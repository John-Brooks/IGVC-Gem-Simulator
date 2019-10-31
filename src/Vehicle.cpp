#include "Vehicle.h"
#include "Geometry.h"
#include <cmath>

Vehicle::Vehicle()
{
	mLastUpdateTimeMs = 0;

	// +/- 60 degrees 
	mMinimumSteeringAngle = M_PI * (-60.0 / 180.0);
	mMaximumSteeringAngle = M_PI * (60.0 / 180.0);
	mCurrentSteeringAngle = 0;
	mYawRate = 0;
	mWheelbase = 2;
	mWidth = 1;
	mLength = 2;

	mMaximumAccel = 1;
	mMinimumAccel = -1;
	mCurrentAccelRequested = 0;
	mMaximumSpeed = 5;
	mCurrentSpeed = 0;
	mBrakeApplied = false;
	mReverse = false;

	mSafetyLightsOn = false;
	mSafetyLightFlash = false;

	//call the base class constructor to create our geometry
	this->DrawableObject::DrawableObject(Rect(Point(0, mWidth / 2.0), Point(mLength, mWidth / -2.0)));
	InitPoseTransformedDrawable();
}

void Vehicle::ProcessSimulationTimeStep(double time_step)
{
	DynamicsUpdate(time_step);
}

void Vehicle::SetSteeringAngle(double new_angle)
{
	//TODO: Add some sort of dynamics where steering response is not instantaneous.
	if (new_angle < mMinimumSteeringAngle)
		mCurrentSteeringAngle = mMinimumSteeringAngle;
	else if (new_angle > mMaximumSteeringAngle)
		mCurrentSteeringAngle = mMaximumSteeringAngle;
	else
		mCurrentSteeringAngle = new_angle;
}

void Vehicle::DynamicsUpdate(double delta_t)
{
	double average_speed = (mCurrentAccelRequested / 2) * delta_t + mCurrentSpeed;

	//within 1 degree use straight line calculation
	if (mCurrentSteeringAngle < 0.005 && mCurrentSteeringAngle > -0.005)
	{
		double s = average_speed * delta_t;
		mPose.pos.x += s * cos(mPose.angle);
		mPose.pos.y += s * sin(mPose.angle);

		mPoseTransformedDrawable->mPose = mPose;
		UpdatePoseTransformedDrawable();
		mCurrentSpeed += mCurrentAccelRequested * delta_t;
		return;
	}
	
	bool steering_right = mCurrentSteeringAngle < 0;
	double steer_right_negate = steering_right ? -1.0 : 1.0;

	//approximating based on constant acceleration (shouldn't need to integrate for small time steps)
	
	
	double turning_radius = abs(mWheelbase / tan(mCurrentSteeringAngle));
	mYawRate = (average_speed / turning_radius) * steer_right_negate; //radians / second (steering left increases vehicle angle.

	double theta_s;
	if (steering_right)
		theta_s = mPose.angle - (M_PI / 2.0);
	else
		theta_s = mPose.angle + (M_PI / 2.0);

	Point str_circle_center;
	str_circle_center.x = mPose.pos.x;
	str_circle_center.x += turning_radius * cos(theta_s);
	str_circle_center.y += mPose.pos.y;
	str_circle_center.y += turning_radius * sin(theta_s);

	Point veh_coord_relative_to_circle_center(mPose.pos.x - str_circle_center.x, mPose.pos.y - str_circle_center.y);

	double turn_circ_current_theta = CalculatePointAngle(veh_coord_relative_to_circle_center);
	double turn_circ_new_theta = turn_circ_current_theta + (mYawRate * delta_t);

	mPose.pos.x = str_circle_center.x + turning_radius * cos(turn_circ_new_theta);
	mPose.pos.y = str_circle_center.y + turning_radius * sin(turn_circ_new_theta);
	mPose.angle += mYawRate * delta_t;
	if(mPose.angle > (2.0 * M_PI))
		mPose.angle -= (2.0 * M_PI);
	mPoseTransformedDrawable->mPose = mPose;
	UpdatePoseTransformedDrawable();
	mCurrentSpeed += mCurrentAccelRequested * delta_t;
}

void Vehicle::SetAccelRequested(double new_accel)
{
	if (new_accel > mMaximumAccel)
		mCurrentAccelRequested = mMaximumAccel;
	else if (new_accel < mMinimumAccel)
		mCurrentAccelRequested = mMinimumAccel;
	else
		mCurrentAccelRequested = new_accel;

}
