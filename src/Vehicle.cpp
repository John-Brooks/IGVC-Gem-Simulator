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

	mVehicleDrawable = DrawableObject(Rect(Point(0, mWidth / 2.0), Point(mLength, mWidth / -2.0)));
	mVehicleDrawable.mColor.r = 255;
	mVehicleDrawable.mColor.g = 0;
	mVehicleDrawable.mColor.b = 0;

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
	double steer_right_negate = mCurrentSteeringAngle > 0 ? 1 : -1;

	//approximating based on constant acceleration (shouldn't need to integrate for small time steps)
	double average_speed = (mCurrentAccelRequested / 2) * delta_t + mCurrentSpeed;
	
	double turning_radius = mWheelbase / tan(mCurrentSteeringAngle);
	mYawRate = (average_speed / turning_radius) * steer_right_negate; //radians / second (steering left increases vehicle angle.

	Point str_circle_center;
	str_circle_center.x = turning_radius * sin(mPose.angle) * steer_right_negate * -1;
	str_circle_center.y = turning_radius * cos(mPose.angle) * steer_right_negate;
	str_circle_center.x += mPose.pos.x;
	str_circle_center.y += mPose.pos.y;

	Point veh_coord_relative_to_circle_center(mPose.pos.x - str_circle_center.x, mPose.pos.y - str_circle_center.y);


	double turn_circ_current_theta = CalculatePointAngle(veh_coord_relative_to_circle_center);
	double turn_circ_new_theta = turn_circ_current_theta + (mYawRate * delta_t);

	mPose.pos.x = str_circle_center.x + turning_radius * cos(turn_circ_new_theta);
	mPose.pos.y = str_circle_center.y + turning_radius * sin(turn_circ_new_theta);
	mPose.angle += mYawRate * delta_t;
	mVehicleDrawable.mPose = mPose;
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
