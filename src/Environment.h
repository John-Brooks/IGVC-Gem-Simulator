#pragma once
#include "Vehicle.h"
#include "Geometry.h"
#include "Graphics.h"


class Environment {
public:
	void Init();
	bool Step();
	void Render();
	double GetReward();


private:
	
	std::vector< DrawableObject* > mRoadLines;
	std::vector< DrawableObject* > mObstacles;
	std::vector< DrawableObject* > mRewardGates;

	Graphics mGraphics;

	Vehicle mVehicle;
};