#pragma once
#include "Geometry.h"

class Vehicle {
public:
	Vehicle();
	void Start();
	void DynamicsUpdate(double delta_t);
	void SetPose(const Pose& new_pose) { mPose = new_pose; mVehicleDrawable.mPose = new_pose; }
	Pose GetPose() { return mPose; }
	void SetBrake(bool brake_on) { mBrakeApplied = brake_on; }
	void SetAccelRequested(double new_accel);
	void SetSafetyLightsOn(bool lights_on) { mSafetyLightsOn = lights_on; }
	void SetSteeringAngle(double new_angle);

	double GetCurrentSpeed() { return mCurrentSpeed; }
	void SetCurrentSpeed(const double& new_speed) { mCurrentSpeed = new_speed; }
	double GetCurrentSteeringAngle() { return mCurrentSteeringAngle; }

	DrawableObject* GetVehicleDrawable() { return &mVehicleDrawable; }

protected:
	//Simulation
	unsigned long long mLastUpdateTimeMs;

	//Positioning
	Pose mPose;
	double mWidth;
	double mLength;

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
	DrawableObject mVehicleDrawable;

};