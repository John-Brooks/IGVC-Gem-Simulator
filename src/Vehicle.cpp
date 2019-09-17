#include "Vehicle.h"
#include "Geometry.h"
#include <cmath>

void Vehicle::Vehicle()
{
	mLastUpdateTimeMs = 0;
}

void Vehicle::SetSteeringAngle(const double& new_angle)
{
	//TODO: Add some sort of dynamics where steering response is not instantaneous.
	if (new_angle < mMinimumSteeringAngle)
		mCurrentSteeringAngle = mMinimumSteeringAngle;
	else if (new_angle > mMaximumSteeringAngle)
		mCurrentSteeringAngle = mMaximumSteeringAngle;
	else
		mCurrentSteeringAngle = new_angle;

	UpdateYawRate();
}

void Vehicle::DynamicsUpdate(const unsigned long long& current_time_ms)
{
	double time_elapsed = (double)(current_time_ms - mLastUpdateTimeMs) / 1000;
	double steer_left_negate = steering_angle > 0 ? 1 : -1;

	//approximating based on constant acceleration (shouldn't need to integrate for small time steps)
	double average_speed = (mCurrentAccelRequested / 2) * time_elapsed + mCurrentSpeed;
	
	double turning_radius = mWheelbase / tan(mCurrentSteeringAngle);
	mYawRate = (average_speed / turning_radius) * mCurrentSteeringAngle < 0 ? 1 : -1; //radians / second (steering left increases vehicle angle.

	Point str_circle_center;
	str_circle_center.x = turning_radius * cos(mPose.angle) * steer_left_negate;
	str_circle_center.y = turning_radius * sin(mPose.angle) * steer_left_negate;
	str_circle_center.x += mPose.pos.x;
	str_circle_center.y += turning_radius * sin(mPose.angle);

	double turn_circ_ang_1 = atan((str_circle_center.y - veh_pos.y) / (str_circle_center.x - mPose.pos.x));
	double turn_circ_ang_2 = turn_circ_ang_1 + (yaw_rate * time_elapsed);

	mPose.pos.x = str_circle_center.x + turn_radius * cos(turn_circ_ang_2);
	mPose.pos.y = str_circle_center.x + turn_radius * sin(turn_circ_ang_2);
	mPose.angle += mYawRate * time_elapsed;

	mCurrentSpeed += mCurrentAccelRequested * time_elapsed;
}

void Vehicle::SetAccelRequested(const double& new_accel)
{
	if (new_accel > mMaximumAccel)
	{
		mCurrentAccelRequested = mMaximumAccel;
	}
	else if( new_accel < mMinimumAccel )
}