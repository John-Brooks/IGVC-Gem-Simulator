#include "Environment.h"
#include "Scenario.h"
#include "Collision.h"

void Environment::Init(Scenario* scenario)
{
	mScenario = scenario;
	Pose vehicle_pose;
	vehicle_pose = scenario->mStartingLocation;
	mVehicle.SetPose(vehicle_pose);
	mVehicleOriginalColor = mVehicle.GetVehicleDrawable()->mColor;
	
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
	mCollision.AddObject(mVehicle.GetVehicleDrawable());
	mCollision.AddObject(mVehicle.GetVehicleDrawable());

	for (auto& drawable : mScenario->mBoundaries)
	{
		mGraphics.AddDrawableObject(&drawable);
		mCollision.AddEnvironment(&drawable);
	}
}

void Environment::Render()
{
	mGraphics.Render();
}

StateSpace Environment::Step(const ActionSpace& action)
{
	StateSpace state;
	mVehicle.SetCurrentSpeed(action.VehicleSpeed);
	mVehicle.SetSteeringAngle(action.SteeringAngle);
	mVehicle.DynamicsUpdate(mSimulationTimeStep);
	mVehicle.GetVehicleDrawable()->mColor = mVehicleOriginalColor;

	std::vector<CollisionDetection> collisions = mCollision.GetObjectCollisions();

	for (auto& collision : collisions)
	{
		for (int i = 0; i < collision.num_collisions; i++)
		{
			collision.object->mColor.r = 255;
			collision.object->mColor.g = 0;
			collision.object->mColor.b = 0;
		}
	}

	state.SteeringAngle = mVehicle.GetCurrentSteeringAngle();
	state.VehicleSpeed = mVehicle.GetCurrentSpeed();
	return state;
}