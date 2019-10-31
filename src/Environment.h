#pragma once
#include "Vehicle.h"
#include "Geometry.h"
#include "Graphics.h"
#include "ActionSpace.h"
#include "StateSpace.h"
#include "Collision.h"
#include <vector>
#include <map>
class Scenario;

class Environment {
public:
	void LoadScenario(Scenario* scenario);
	StateSpace Step(const ActionSpace& action);
	void Render();
	void Reset();

	void SetRewardGateValue(double reward);
	void SetCrashRewardValue(double reward);

	void SetSimulationTimeStep(double time_step) { mSimulationTimeStep = time_step; }
	
private:
	void CheckCollisions();
	void ProcessVehicleCollision(std::shared_ptr<ScenarioObject> object);

	Graphics mGraphics;
	Collision mCollision;
	StateSpace mStateSpace;

	std::shared_ptr<Vehicle> mVehicle = std::make_shared<Vehicle>();
	DrawableObject::Color mVehicleOriginalColor;

	Scenario* mScenario;

	double mRewardGateReward = 10;
	double mCrashReward = -200;

	double mSimulationTimeStep;
};