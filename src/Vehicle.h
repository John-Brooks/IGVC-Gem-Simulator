#pragma once
#include "Geometry.h"

class Vehicle {
public:
	Vehicle();
	void Start(const unsigned long long& current_time_ms);
	void DynamicsUpdate(const unsigned long long& current_time_ms);
	void SetPose(const Pose& new_pose) { mPose = new_pose; }
	void SetBrake(const bool& brake_on) { mBrakeApplied = brake_on; }
	void SetAccelRequested(const double& new_accel);
	void SetSafetyLightsOn(const bool& lights_on) { mSafetyLightsOn = lights_on; }
	void SetSteeringAngle(const double& new_angle);

	double GetCurrentSpeed() { return mCurrentSpeed; }
	double GetCurrentSteeringAngle() { return mCurrentSteeringAngle; }

protected:
	//Simulation
	unsigned long long mLastUpdateTimeMs;

	//Positioning
	Pose mPose;

	//Steering
	double mMinimumSteeringAngle;
	double mMaximumSteeringAngle;
	double mCurrentSteeringAngle;
	double mYawRate;
	double mWheelbase;

	//Drive System
	double mMaximumAccel;
	double mMinimumAccel;
	double mCurrentAccelRequested;
	double mMaximumSpeed;
	double mCurrentSpeed;
	bool mBrakeApplied;
	bool mReverse;

	//Misc
	bool mSafetyLightsOn;
	bool mSafetyLightFlash;

};