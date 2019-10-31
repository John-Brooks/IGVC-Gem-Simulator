#pragma once

#include "geometry.h"
#include <map>

//The collision class tracks objects like the vehicle (a rectangle, or perhaps a collection of rectangles / lines)
//and any other lines

#define MAX_COLLISIONS 10

struct CollisionDetection
{
	DrawableObject* object;
	DrawableObject* collidided_objs[MAX_COLLISIONS];
	size_t num_collisions = 0;
};

class Collision
{
public:
	//All geometry in an object is checked against the geometry of
	//every other object and environment
	void AddObject(DrawableObject* object) {
		mObjects.push_back(object);
	}

	//Environment objects are not checked to have collided with anything other than
	//regular objects. i.e. we do not check if the road collided with the road.
	void AddEnvironment(DrawableObject* object) {
		mEnvironment.push_back(object);
	}

	void Clear() {
		mObjects.clear();
		mEnvironment.clear();
	}

	std::vector< CollisionDetection > GetObjectCollisions();

private:
	int mLastObjectID;
	std::vector< DrawableObject* > mObjects;
	std::vector< DrawableObject* > mEnvironment;

};