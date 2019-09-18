#pragma once
#include <vector>

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
};
struct Line {
	Point p1, p2;
	Line(Point p1, Point p2) : p1(p1), p2(p2) {}
	Line(){}
};
struct Rect {
    Point top_left, bottom_right;
};
struct Object
{
	std::vector< Line > lines;

	Object(const Rect& rect)
	{
		const Point& top_left = rect.top_left;
		const Point& bottom_right = rect.top_left;
		Point top_right(rect.bottom_right.x, rect.top_left.y);
		Point bottom_left(rect.top_left.x, rect.bottom_right.y);
		
		lines.push_back(Line(top_left, top_right)); //top
		lines.push_back(Line(top_right, bottom_right)); //right
		lines.push_back(Line(bottom_right, bottom_left)); //bottom
		lines.push_back(Line(bottom_left, top_left)); //left
	}
	Object(const Line& line)
	{
		lines.push_back(line);
	}
};
struct Pose
{
	Point pos;
	double angle;
};


