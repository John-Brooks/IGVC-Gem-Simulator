#pragma once



class Vehicle {
public:
	struct Pose
	{
		double x, y, angle;
	};
	
	void DynamicsUpdate(const unsigned long long& current_time_ms);
	void SetPose(const Pose& new_pose);
	void SetBrake(const bool& brake_on);
	void SetAccelRequested(const double& new_accel);
	void SetSafetyLightsOn(const bool& lights_on);
	void SetSteeringAngle(const double& new_angle);

	double GetCurrentSpeed() { return mCurrentSpeed; }
	double GetCurrentSteeringAngle() { return mCurrentSteeringAngle; }

protected:
	//Simulation
	unsigned long long mLastUpdateTimeMs;

	//Steering
	double mMinimumSteeringAngle;
	double mMaximumSteeringAngle;
	double mCurrentSteeringAngle;
	double mYawRate;

	//Drive System
	double mMaximumAccel;
	double mCurrentAccelRequested;
	double mMaximumSpeed;
	double mCurrentSpeed;
	bool mBrakeApplied;
	bool mReverse;

	//Misc
	bool mSafetyLightsOn;
	bool mSafetyLightFlash;

	void UpdateYawRate();

};