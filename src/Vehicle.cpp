#include "Vehicle.h"
#include <cmath>

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