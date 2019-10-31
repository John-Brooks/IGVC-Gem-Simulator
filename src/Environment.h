#pragma once
#include "Vehicle.h"
#include "Geometry.h"
#include "Graphics.h"
#include "ActionSpace.h"
#include "StateSpace.h"
#include "Collision.h"
class Scenario;


class Environment {
public:
	void Init(Scenario* scenario);
	StateSpace Step(const ActionSpace& action);
	void Render();
	double GetReward();

	void SetSimulationTimeStep(double time_step) { mSimulationTimeStep = time_step; }


	

private:
	
	std::vector< DrawableObject* > mRoadLines;
	std::vector< DrawableObject* > mObstacles;
	std::vector< DrawableObject* > mRewardGates;

	Graphics mGraphics;
	Collision mCollision;

	Vehicle mVehicle;
	DrawableObject::Color mVehicleOriginalColor;

	Scenario* mScenario;

	double mSimulationTimeStep;
};