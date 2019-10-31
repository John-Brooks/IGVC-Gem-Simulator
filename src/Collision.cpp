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

bool ObjectsCollide(const DrawableObject* object1, const DrawableObject* object2)
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
				return true;
			}

		}
	}
	return false;
}

std::vector< CollisionDetection > Collision::GetObjectCollisions()
{
	std::vector< CollisionDetection > ret;

	for (auto p_collidable : mObjects)
	{
		DrawableObject collidable = *p_collidable;
		CollisionDetection detection;

		for (auto& line : collidable.mLines)
		{
			ApplyObjectPose(line, collidable.mPose);
		}

		for (const auto& obj : mObjects)
		{
			if (p_collidable == obj)
				continue;
			if (ObjectsCollide(&collidable, obj))
			{
				detection.object = p_collidable;
				detection.collidided_objs[detection.num_collisions++] = obj;
			}
		}

		for (const auto& obj : mEnvironment)
		{
			if (ObjectsCollide(&collidable, obj))
			{
				detection.object = p_collidable;
				detection.collidided_objs[detection.num_collisions++] = obj;
			}
		}

		if (detection.num_collisions > 0)
			ret.push_back(detection);
	}

	return ret;
}