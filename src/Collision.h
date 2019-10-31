#pragma once

#include "Geometry.h"
#include "SimulationObject.h"
#include "ScenarioObject.h"
#include <map>
#include <memory>

//The collision class tracks objects like the vehicle (a rectangle, or perhaps a collection of rectangles / lines)
//and any other lines

struct CollisionDetection
{
	std::shared_ptr< SimulationObject > object;
	std::vector< std::shared_ptr< ScenarioObject > > collidided_objs;
};

class Collision
{
public:
	//All geometry in an object is checked against the geometry of
	//every other object and environment
	void AddSimulationObject(std::shared_ptr< SimulationObject > object) {
		mSimulationObjects.push_back(object);
	}

	//Environment objects are not checked to have collided with anything other than
	//regular objects. i.e. we do not check if the road collided with the road.
	void AddEnvironmentObject(std::shared_ptr< ScenarioObject > object) {
		mEnvironmentObjects.push_back(object);
	}

	void RemoveEnvironmentObject(std::shared_ptr< ScenarioObject > object);

	void Clear() {
		mSimulationObjects.clear();
		mEnvironmentObjects.clear();
	}

	std::vector< CollisionDetection > GetObjectCollisions();

private:
	std::vector< std::shared_ptr< SimulationObject > > mSimulationObjects;
	std::vector< std::shared_ptr< ScenarioObject > > mEnvironmentObjects;

};
