#pragma once
#include "Geometry.h"

enum class ObjectType {
	Vehicle,
	VehiclePointSensor,
	RewardGate,
	EndZone,
	LaneLine,
	Unknown,
};

class ScenarioObject : public DrawableObject
{
public:
	using DrawableObject::DrawableObject;
	ObjectType mType;
};