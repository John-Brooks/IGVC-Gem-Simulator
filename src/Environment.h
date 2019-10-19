#pragma once
#include "Vehicle.h"
#include "Geometry.h"
#include "Graphics.h"
#include "ActionSpace.h"
#include "StateSpace.h"


class Environment {
public:
	void Init();
	StateSpace Step(const ActionSpace& action);
	void Render();
	double GetReward();

	void SetSimulationTimeStep(double time_step) { mSimulationTimeStep = time_step; }


private:
	
	std::vector< DrawableObject* > mRoadLines;
	std::vector< DrawableObject* > mObstacles;
	std::vector< DrawableObject* > mRewardGates;

	Graphics mGraphics;

	Vehicle mVehicle;

	double mSimulationTimeStep;
};