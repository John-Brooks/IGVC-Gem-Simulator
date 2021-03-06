#include "Collision.h"

bool CheckVerticalLine(const Line& vert, const Line& reg)
{
	//if the vertical line is outside the domain of the regular line
	if (reg.min_x > vert.p1.x || reg.max_x < vert.p1.x)
		return false;

	double vert_max_y = vert.p1.y > vert.p2.y ? vert.p1.y : vert.p2.y;
	double vert_min_y = vert.p1.y < vert.p2.y ? vert.p1.y : vert.p2.y;

	double y_intercept = (reg.slope * vert.p1.x) + reg.intercept;

	return y_intercept < vert_max_y&& y_intercept > vert_min_y;
}

bool ObjectsCollide(std::shared_ptr<const DrawableObject> object1, std::shared_ptr<const DrawableObject> object2, Point& point_of_collision)
{
	double x_intercept;
	for (const auto& l1 : object1->mLines)
	{
		for (const auto& l2 : object2->mLines)
		{
			//handling degenerate cases...
			if (l1.slope == l2.slope)
			{
				//parallel lines
				continue;
			}
			else if (l1.vertical)
			{
				//line 1 is verticle, check for a verticle intercept
				if (CheckVerticalLine(l1, l2))
					return true;
				else
					continue;
			}
			else if (l2.vertical)
			{
				//line 2 is verticle, check for a verticle intercept
				if (CheckVerticalLine(l2, l1))
					return true;
				else
					continue;
			}

			//normal case
			x_intercept = (l1.intercept - l2.intercept) / (l2.slope - l1.slope);
			if (x_intercept > l1.min_x &&
				x_intercept > l2.min_x &&
				x_intercept < l1.max_x &&
				x_intercept < l2.max_x)
			{
				point_of_collision.x = x_intercept;
				point_of_collision.y = (x_intercept * l1.slope) + l1.intercept;
				return true;
			}

		}
	}
	return false;
}

std::vector< CollisionDetection > Collision::GetObjectCollisions()
{
	std::vector< CollisionDetection > ret;

	for (const auto collidable : mSimulationObjects)
	{
		CollisionDetection detection;
		Point point_of_collision;
		for (const auto& obj : mSimulationObjects)
		{
			if (collidable == obj)
				continue;
			if (ObjectsCollide(collidable->mPoseTransformedDrawable, obj->mPoseTransformedDrawable, point_of_collision))
			{
				detection.object = collidable;
				detection.collidided_objs.push_back(obj);
				detection.collision_points.push_back(point_of_collision);
			}
		}

		for (const auto& obj : mEnvironmentObjects)
		{
			if (ObjectsCollide(collidable->mPoseTransformedDrawable, obj, point_of_collision))
			{
				detection.object = collidable;
				detection.collidided_objs.push_back(obj);
				detection.collision_points.push_back(point_of_collision);
			}
		}

		if (detection.collidided_objs.size() > 0)
			ret.push_back(detection);
	}

	return ret;
}

void Collision::RemoveEnvironmentObject(std::shared_ptr< ScenarioObject > object)
{
	auto it = mEnvironmentObjects.begin();
	while (*it != object && it != mEnvironmentObjects.end())
		it++;
	if (it != mEnvironmentObjects.end())
	{
		mEnvironmentObjects.erase(it);
	}
}