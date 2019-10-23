#include "Environment.h"
#include "Scenario.h"


void Environment::Init(Scenario* scenario)
{
	mScenario = scenario;
	Pose vehicle_pose;
	vehicle_pose = scenario->mStartingLocation;
	mVehicle.SetPose(vehicle_pose);
	
	
	if (mScenario->mWidth / mScenario->mHeight > 1920.0 / 1080.0)
	{
		//Wider than 1920x1080
		mGraphics.SetEnvironmentHeight(mScenario->mWidth * (1080.0 / 1920.0));
		mGraphics.SetEnvironmentWidth(mScenario->mWidth);
	}
	else
	{
		mGraphics.SetEnvironmentHeight(mScenario->mHeight);
		mGraphics.SetEnvironmentWidth(mScenario->mHeight * (1920.0 / 1080.0));
	}

	mGraphics.SetWindowSize(1920, 1080);
	mGraphics.Init();

	mGraphics.AddDrawableObject(mVehicle.GetVehicleDrawable());

	for (auto& drawable : mScenario->mBoundaries)
	{
		mGraphics.AddDrawableObject(&drawable);
	}
}

void Environment::Render()
{
	//Pose pose = mVehicle.GetPose();
	//pose.angle += 0.01;
	//mVehicle.SetPose(pose);
	mGraphics.Render();
}

StateSpace Environment::Step(const ActionSpace& action)
{
	StateSpace state;
	mVehicle.SetCurrentSpeed(action.VehicleSpeed);
	mVehicle.SetSteeringAngle(action.SteeringAngle);
	mVehicle.DynamicsUpdate(mSimulationTimeStep);

	state.SteeringAngle = mVehicle.GetCurrentSteeringAngle();
	state.VehicleSpeed = mVehicle.GetCurrentSpeed();
	return state;
}