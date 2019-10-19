#pragma once

#include "geometry.h"
#include <map>

//The collision class tracks objects like the vehicle (a rectangle, or perhaps a collection of rectangles / lines)
//and any other lines

class Collision
{
public:
	Collision();

	void AddObject(int& object_id, const DrawableObject& object);
	bool DeleteObject(int object_id);

	std::vector< int > GetObjectCollisions();

private:
	int mLastObjectID;
	std::map< int, DrawableObject > mObjects;

};