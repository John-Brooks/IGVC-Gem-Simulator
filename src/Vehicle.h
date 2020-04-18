#pragma once
#include "Geometry.h"
#include "SimulationObject.h"
#include "DistanceSensor.h"

class Vehicle : public SimulationObject
{
public:
	Vehicle();
	void Reset();
	void ProcessSimulationTimeStep(double time_step);
	void DynamicsUpdate(double delta_t);
	void SetPose(const Pose& new_pose) { mPose = new_pose; mPoseTransformedDrawable->mPose = new_pose; }
	Pose GetPose() { return mPose; }
	void SetBrake(bool brake_on) { mBrakeApplied = brake_on; }
	void SetAccelRequested(double new_accel);
	void SetSafetyLightsOn(bool lights_on) { mSafetyLightsOn = lights_on; }
	void SetSteeringAngle(double new_angle);

	double GetCurrentSpeed() { return mCurrentSpeed; }
	void SetCurrentSpeed(const double& new_speed) { mCurrentSpeed = new_speed; }
	double GetCurrentSteeringAngle() { return mCurrentSteeringAngle; }

	std::vector< std::shared_ptr<DistanceSensor> > mDistanceSensors;

protected:
	//Simulation
	unsigned long long mLastUpdateTimeMs;

	//Positioning
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
};