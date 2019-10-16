#pragma once
#include <vector>

class Point {
public:
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
};
class Line{
public:
	Point p1, p2;
	Line(Point p1, Point p2) : p1(p1), p2(p2) {}
	Line(){}
};
class Circle
{
public:
	double x, y, r;
};
struct Pose
{
	Point pos;
	double angle;
};
class Object
{
public:
	std::vector< Line > lines;
	std::vector< Circle > circles;
	Object() = default;
	Object(const Line& line)
	{
		lines.push_back(line);
	}
	Object(const Circle& circle)
	{
		circles.push_back(circle);
	}
};
class Rect : public Object {
public:
	Rect(const Point& top_left, const Point& bottom_right)
	{
		Point top_right = Point(bottom_right.x, top_left.y);
		Point bottom_left = Point(top_left.x, bottom_right.y);

		lines.push_back(Line(top_left, top_right)); //top
		lines.push_back(Line(top_right, bottom_right)); //right
		lines.push_back(Line(bottom_right, bottom_left)); //bottom
		lines.push_back(Line(bottom_left, top_left)); //left
	}
	Pose mPose;
};



