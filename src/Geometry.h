#pragma once
#include <vector>
#include <stdint.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846  /* pi */
#endif

struct Point {
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point() : x(0), y(0) {}
};
struct Line{
	Point p1, p2;
	Line(Point p1, Point p2) : p1(p1), p2(p2) {
		UpdateMetaData();
	}

	void UpdateMetaData()
	{
		if (p2.x - p1.x != 0)
		{
			slope = (p2.y - p1.y) / (p2.x - p1.x);
			vertical = false;
		}
		else
		{
			vertical = true;
			slope = 0;
		}

		intercept = p2.y - (slope * p2.x);
		if (p1.x < p2.x)
		{
			min_x = p1.x;
			max_x = p2.x;
		}
		else
		{
			min_x = p2.x;
			max_x = p1.x;
		}
	}
	double slope = 0;
	double intercept = 0;
	double min_x = 0;
	double max_x = 0;
	bool vertical = false;
};
struct Circle
{
	double x, y, r;
};
struct Rect {
	Rect(const Point& top_left_in, const Point& bottom_right_in) :	top_left(top_left_in), 
																	bottom_right(bottom_right_in),
																	top_right(bottom_right.x, top_left.y),
																	bottom_left(top_left.x, bottom_right.y) {}

	void SetPoints(const Point& top_left_in, const Point& bottom_right_in)
	{
		top_left = top_left_in;
		bottom_right = bottom_right_in;
		top_right = Point(bottom_right.x, top_left.y);
		bottom_left = Point(top_left.x, bottom_right.y);
	}

	Point top_left;
	Point bottom_right;
	Point top_right;
	Point bottom_left;
};
struct Pose
{
	Pose() : pos(0,0), angle(0) {}
	Point pos;
	double angle;
};

struct DrawableObject
{
	DrawableObject()
	{
		mPixelCoordinates = false;
	}
	DrawableObject(const Line& line)
	{
		SetupFromLine(line);
	}
	void SetupFromLine(const Line& line)
	{
		mLines.clear();
		mCircles.clear();
		mLines.push_back(line);
		mPixelCoordinates = false;
		mWidth = line.p1.x - line.p2.x;
		if (mWidth < 0.0)
			mWidth *= -1.0;

		mHeight = line.p1.y - line.p2.y;
		if (mHeight < 0.0)
			mHeight *= -1.0;

		mCenter.x = (line.p1.x + line.p2.x) / 2.0;
		mCenter.y = (line.p1.y + line.p2.y) / 2.0;
	}
	DrawableObject(const Circle& circle)
	{
		SetupFromCircle(circle);
	}
	void SetupFromCircle(const Circle& circle)
	{
		mLines.clear();
		mCircles.clear();
		mCircles.push_back(circle);
		mPixelCoordinates = false;
		mCenter.x = circle.x;
		mCenter.y = circle.y;
		mWidth = mHeight = circle.r;
	}
	DrawableObject(const Rect& rect)
	{
		SetupFromRect(rect);
	}
	void SetupFromRect(const Rect& rect)
	{
		mLines.clear();
		mCircles.clear();
		mLines.push_back(Line(rect.top_left, rect.top_right)); //top
		mLines.push_back(Line(rect.top_right, rect.bottom_right)); //right
		mLines.push_back(Line(rect.bottom_right, rect.bottom_left)); //bottom
		mLines.push_back(Line(rect.bottom_left, rect.top_left)); //left
		mPixelCoordinates = false;
		mWidth = rect.top_right.x - rect.top_left.x;
		mHeight = rect.top_left.y - rect.bottom_left.y;
		mCenter.x = (rect.top_left.x + rect.top_right.x) / 2.0;
		mCenter.y = (rect.top_left.y + rect.bottom_left.y) / 2.0;
		if (mWidth < 0.0)
			mWidth *= -1.0;

		if (mHeight < 0.0)
			mHeight *= -1.0;
	}
	std::vector< Line > mLines;
	std::vector< Circle > mCircles;
	double mWidth = 0;
	double mHeight = 0;
	Point mCenter;

	struct Color
	{
		Color() : r(255), g(255), b(255), a(255) {}
		uint8_t r, g, b, a;

	} mColor;

	bool mPixelCoordinates;
	Pose mPose;
};

static double CalculatePointAngle(const Point& point)
{
	double theta;
	if (point.x == 0.0)
	{
		if (point.y >= 0.0)
			theta = M_PI / 2.0;
		else
			theta = M_PI * 3 / 2;
	}
	else
	{
		theta = atan(point.y / point.x);
		if ((point.x < 0 && point.y > 0) || (point.x < 0 && point.y < 0)) //quadrant 2 || 3
		{
			theta += M_PI;
		}
	}
	return theta;
}

static void ApplyObjectAngleToPoint(Point& point, const Pose& pose)
{
	double r, theta;

	r = sqrt(pow(point.y, 2) + pow(point.x, 2));

	theta = CalculatePointAngle(point);
	theta += pose.angle;
	point.x = r * cos(theta);
	point.y = r * sin(theta);
}

static void ApplyObjectPose(Line & line, const Pose & pose)
{
	if (pose.angle != 0.0)
	{
		ApplyObjectAngleToPoint(line.p1, pose);
		ApplyObjectAngleToPoint(line.p2, pose);
	}

	line.p1.x += pose.pos.x;
	line.p1.y += pose.pos.y;
	line.p2.x += pose.pos.x;
	line.p2.y += pose.pos.y;

	line.UpdateMetaData();
}
static double PointDistance(const Point& p1, const Point& p2)
{
	double x = p2.x - p1.x;
	double y = p2.y - p1.y;

	return sqrt(pow(x, 2) + pow(y, 2));
}


