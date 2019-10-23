#pragma once
#include "Geometry.h"
#include "tinyxml2.h"
#include <string> 

class Scenario
{
public:
	bool ConvertFile(std::string path);

	std::vector< DrawableObject > mRewardGates;
	std::vector< DrawableObject > mBoundaries;
	std::vector< DrawableObject > mObstacles;

	Pose mStartingLocation;
	DrawableObject mEndZone;

	double mWidth, mHeight;

	double mXTranslation, mYTranslation;

private:
	struct RGBValue_t
	{
		unsigned char r, g, b;
	};


	bool ReadMapSize(tinyxml2::XMLElement* svg);
	bool ReadPaths(tinyxml2::XMLElement* svg);
	bool ReadRects(tinyxml2::XMLElement* parent);
	bool ConvertPathToLineDrawable(tinyxml2::XMLElement* path, DrawableObject& object);
	bool PathIsStartLocationMarker(tinyxml2::XMLElement* path);
	bool ReadAndSetStartLocation(tinyxml2::XMLElement* path);
	bool ConvertRectToDrawable(tinyxml2::XMLElement* path, DrawableObject& object);
	RGBValue_t GetStrokeColorFromStyle(const std::string& style);
	RGBValue_t GetFillColorFromStyle(const std::string& style);
	Line ConvertDimensionToLine(const std::string& dimension);
	void UpdateTranslation(const std::string& transform);


};