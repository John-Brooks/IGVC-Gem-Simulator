#include "Environment.h"
#include "Scenario.h"
#include "Collision.h"
#include "EndZone.h"

bool Environment::LoadScenario(const char* filepath)
{
	mScenario.ConvertFile(filepath);
	
	mCollision.Clear();
	mGraphics.Close();

	mVehicle->SetPose(mScenario.mStartingLocation);
	mVehicleOriginalColor = mVehicle->mColor;
	
	if (mScenario.mWidth / mScenario.mHeight > mWindowWidth / mWindowHeight)
	{
		//Wider than our current aspect ratio
		mGraphics.SetEnvironmentHeight(mScenario.mWidth * (mWindowHeight / mWindowWidth));
		mGraphics.SetEnvironmentWidth(mScenario.mWidth);
	}
	else
	{
		mGraphics.SetEnvironmentHeight(mScenario.mHeight);
		mGraphics.SetEnvironmentWidth(mScenario.mHeight * (mWindowWidth / mWindowHeight));
	}

	mGraphics.SetWindowSize(mWindowWidth, mWindowHeight);

	Reset();
}
void Environment::Close()
{
	mGraphics.Close();
}

void Environment::SetWindowSize(int width, int height)
{
	mWindowWidth = width;
	mWindowHeight = height;
}

void Environment::Reset()
{
	mStateSpace = StateSpace();
	mVehicle->Reset();
	mVehicle->SetPose(mScenario.mStartingLocation);
	mVehicleOriginalColor = mVehicle->mColor;

	mCollision.Clear();
	mGraphics.ClearDrawableObjects();

	mGraphics.AddDrawableObject(mVehicle->mPoseTransformedDrawable);
	for( auto& sensor : mVehicle->mDistanceSensors)
	{
		mGraphics.AddDrawableObject(sensor->mDrawable);
	}

	mCollision.AddSimulationObject(mVehicle);
	for( auto& sensor : mVehicle->mDistanceSensors)
	{
		mCollision.AddSimulationObject(sensor);
	}

	for (auto& obj : mScenario.mObjects)
	{
		mGraphics.AddDrawableObject(obj);
		mCollision.AddEnvironmentObject(obj);
	}
}

bool Environment::Render()
{
	return mGraphics.Render();
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
				break;
			case ObjectType::VehicleDistanceSensor:
				std::static_pointer_cast<DistanceSensor>(collision.object)->ProcessCollision(collision);
				break;
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

	int i = 0;
	for( const auto& sensor : mVehicle->mDistanceSensors)
	{
		mStateSpace.distances[i] = sensor->mDistance;
		i++;
	}

	if (mScenario.mEndZone)
		mStateSpace.reward += mScenario.mEndZone->GetPositionBasedReward(mVehicle->mPoseTransformedDrawable->mPose, action.VehicleStopped);

	mStateSpace.SteeringAngle = mVehicle->GetCurrentSteeringAngle();
	mStateSpace.VehicleSpeed = mVehicle->GetCurrentSpeed();
	return mStateSpace;
}