#include "Environment.h"
#include "Scenario.h"
#include "Collision.h"

void Environment::Init(Scenario* scenario)
{
	mScenario = scenario;
	Pose vehicle_pose;
	vehicle_pose = scenario->mStartingLocation;
	mVehicle->SetPose(vehicle_pose);
	mVehicleOriginalColor = mVehicle->mColor;
	
	if (mScenario->mWidth / mScenario->mHeight > 1920.0 / 1080.0)
	{
		//Wider than our current aspect ratio
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

	mGraphics.AddDrawableObject(mVehicle->mPoseTransformedDrawable);
	mCollision.AddSimulationObject(mVehicle);

	for (auto& obj : mScenario->mObjects)
	{
		mGraphics.AddDrawableObject(obj);
		mCollision.AddEnvironmentObject(obj);
	}
}

void Environment::Render()
{
	mGraphics.Render();
}

StateSpace Environment::Step(const ActionSpace& action)
{
	StateSpace state;
	mVehicle->SetCurrentSpeed(action.VehicleSpeed);
	mVehicle->SetSteeringAngle(action.SteeringAngle);
	mVehicle->ProcessSimulationTimeStep(mSimulationTimeStep);
	mVehicle->mPoseTransformedDrawable->mColor = mVehicleOriginalColor;


	std::vector<CollisionDetection> collisions = mCollision.GetObjectCollisions();

	for (auto& collision : collisions)
	{
		for (int i = 0; i < collision.collidided_objs.size(); i++)
		{
			collision.object->mPoseTransformedDrawable->mColor.r = 255;
			collision.object->mPoseTransformedDrawable->mColor.g = 0;
			collision.object->mPoseTransformedDrawable->mColor.b = 0;
		}
	}

	state.SteeringAngle = mVehicle->GetCurrentSteeringAngle();
	state.VehicleSpeed = mVehicle->GetCurrentSpeed();
	return state;
}