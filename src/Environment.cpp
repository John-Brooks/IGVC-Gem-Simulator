#include "Environment.h"
#include "Scenario.h"
#include "Collision.h"
#include "EndZone.h"

void Environment::LoadScenario(Scenario* scenario)
{
	mCollision.Clear();
	mGraphics.Close();

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

void Environment::Reset()
{
	mStateSpace = StateSpace();
	mVehicle->Reset();
	mVehicle->SetPose(mScenario->mStartingLocation);
	mVehicleOriginalColor = mVehicle->mColor;

	mCollision.Clear();
	mGraphics.ClearDrawableObjects();

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

void Environment::CheckCollisions()
{
	std::vector<CollisionDetection> collisions = mCollision.GetObjectCollisions();

	for (auto& collision : collisions)
	{
		switch (collision.object->mType)
		{
			case ObjectType::Vehicle:
				for (auto& object : collision.collidided_objs)
					ProcessVehicleCollision(object);
		}
	}
}

void Environment::ProcessVehicleCollision(std::shared_ptr<ScenarioObject> object)
{
	switch (object->mType)
	{
	case ObjectType::RewardGate:
		mStateSpace.reward += mRewardGateReward;
		mCollision.RemoveEnvironmentObject(object);
		mGraphics.RemoveDrawableObject(object);
		break;
	case ObjectType::LaneLine:
		mStateSpace.test_ended = true;
		mStateSpace.reward += mCrashReward;
		break;
	default:
		break;
	}
}

void Environment::SetRewardGateValue(double reward)
{
	mRewardGateReward = reward;
}
void Environment::SetCrashRewardValue(double reward)
{
	mCrashReward = reward;
}
StateSpace Environment::Step(const ActionSpace& action)
{
	mStateSpace.reward = 0;
	mVehicle->SetCurrentSpeed(action.VehicleSpeed);
	mVehicle->SetSteeringAngle(action.SteeringAngle);
	mVehicle->ProcessSimulationTimeStep(mSimulationTimeStep);
	mVehicle->mPoseTransformedDrawable->mColor = mVehicleOriginalColor;

	CheckCollisions();

	if (mScenario->mEndZone)
		mStateSpace.reward += mScenario->mEndZone->GetPositionBasedReward(mVehicle->mPoseTransformedDrawable->mPose, action.VehicleStopped);
	
	if (mStateSpace.reward != 0)
		printf("Reward: %0.1f\n", mStateSpace.reward);

	mStateSpace.SteeringAngle = mVehicle->GetCurrentSteeringAngle();
	mStateSpace.VehicleSpeed = mVehicle->GetCurrentSpeed();
	return mStateSpace;
}