#include "EndZone.h"
#include "Geometry.h"
#include <cmath>

EndZone::EndZone(const ScenarioObject& object)
{
	*(ScenarioObject*)this = object;

	mHorizontal = mWidth > mHeight;

	mType = ObjectType::EndZone;
}

double EndZone::GetPositionBasedReward(Pose VehiclePose, bool VehicleStopped)
{
	if (mFirstUpdate)
	{
		mFirstUpdate = false;
		mLastVehiclePose = VehiclePose;
	}


	double reward = 0.0;

	double last_distance = PointDistance(mCenter, mLastVehiclePose.pos);
	double new_distance = PointDistance(mCenter, VehiclePose.pos);

	if (last_distance > new_distance)
		reward += (last_distance - new_distance) * mForwardProgressCoeff;
	else
		reward += (last_distance - new_distance) * mReverseProgressCoeff;

	//when the vehicle signals to stop we award bonuses for how close it got
	if (VehicleStopped)
	{
		//calculate how crooked the car is
		double angle = VehiclePose.angle;

		//equivalent of modulus for double
		while (angle > M_PI)
			angle -= M_PI;

		if (mHorizontal && angle > M_PI / 2)
		{
			angle = M_PI - angle;
		}
		else if (!mHorizontal)
		{
			if (angle > M_PI / 2)
				angle = angle - (M_PI / 2);
			else
				angle = (M_PI / 2) - angle;
		}
		reward -= angle * mEndingAngleCoeff;

		reward -= new_distance * mEndingProximityCoeff;

	}
	mLastVehiclePose = VehiclePose;
	return reward;
}