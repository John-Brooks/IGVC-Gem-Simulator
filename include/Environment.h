#pragma once

#include "Vehicle.h"
#include "Geometry.h"
#include "Graphics.h"
#include "ActionSpace.h"
#include "StateSpace.h"
#include "Collision.h"
#include "Scenario.h"
#include <vector>
#include <map>

class Environment {
public:
	bool LoadScenario(const char* filepath);
	StateSpace Step(const ActionSpace& action);
	bool Render();
	void Close();
	void Reset();

	void SetRewardGateValue(double reward);
	void SetCrashRewardValue(double reward);
	void SetWindowSize(int width, int height);
	void SetSimulationTimeStep(double time_step) { mSimulationTimeStep = time_step; }
	
private:
	void CheckCollisions();
	void ProcessVehicleCollision(std::shared_ptr<ScenarioObject> object);

	Graphics mGraphics;
	Collision mCollision;
	StateSpace mStateSpace;

	std::shared_ptr<Vehicle> mVehicle = std::make_shared<Vehicle>();
	DrawableObject::Color mVehicleOriginalColor;

	Scenario mScenario;

	double mRewardGateReward = 10;
	double mCrashReward = -200;

	double mSimulationTimeStep;

	int mWindowWidth = 1024;
	int mWindowHeight = 768;
};