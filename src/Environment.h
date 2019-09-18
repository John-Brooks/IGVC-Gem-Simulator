#pragma once
#include "Vehicle.h"
#include "Geometry.h"


class Environment {


private:
	std::vector< Object > mRoadLines;
	Vehicle mVehicle;
};