#pragma once
#include "ScenarioObject.h"

class EndZone : public ScenarioObject
{
public:
	EndZone() {
		mType = ObjectType::EndZone;
	};

	EndZone(const ScenarioObject& object);

	double GetPositionBasedReward(Pose VehiclePose, bool VehicleStopped);

	double mForwardProgressCoeff = 20.0;
	double mReverseProgressCoeff = 20;
	double mEndingProximityCoeff = 1;
	double mEndingAngleCoeff = 1;

private:
	bool mHorizontal = false;
	bool mFirstUpdate = true;
	Pose mLastVehiclePose;
};