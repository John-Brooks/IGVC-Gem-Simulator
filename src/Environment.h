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
	void Init(Scenario* scenario);
	StateSpace Step(const ActionSpace& action);
	void Render();
	double GetReward();

	void SetSimulationTimeStep(double time_step) { mSimulationTimeStep = time_step; }
	
private:
	Graphics mGraphics;
	Collision mCollision;

	std::shared_ptr<Vehicle> mVehicle = std::make_shared<Vehicle>();
	DrawableObject::Color mVehicleOriginalColor;

	Scenario* mScenario;

	double mSimulationTimeStep;
};