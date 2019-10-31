#pragma once
#include "Geometry.h"
#include "ScenarioObject.h"
#include "EndZone.h"
#include "tinyxml2.h"
#include <string> 
#include <memory>

class Scenario
{
public:
	bool ConvertFile(std::string path);

	std::vector< std::shared_ptr< ScenarioObject > > mObjects;

	Pose mStartingLocation;

	std::shared_ptr< EndZone > mEndZone;

	double mWidth, mHeight;

	double mXTranslation, mYTranslation;

	

private:
	struct RGBValue_t
	{
		unsigned char r, g, b;
	};
	enum class VectorShape {
		Line,
		Circle,
		Rectangle
	};


	bool ReadMapSize(tinyxml2::XMLElement* svg);
	bool ReadPaths(tinyxml2::XMLElement* svg);
	bool ReadRects(tinyxml2::XMLElement* parent);
	bool ConvertPathToLineDrawable(tinyxml2::XMLElement* path, ScenarioObject& object);
	bool PathIsStartLocationMarker(tinyxml2::XMLElement* path);
	bool ReadAndSetStartLocation(tinyxml2::XMLElement* path);
	bool ConvertRectToDrawable(tinyxml2::XMLElement* path, ScenarioObject& object);
	RGBValue_t GetStrokeColorFromStyle(const std::string& style);
	RGBValue_t GetFillColorFromStyle(const std::string& style);
	Line ConvertDimensionToLine(const std::string& dimension);
	void UpdateTranslation(const std::string& transform);
	bool ImportToScenarioObjects(const ScenarioObject& object, VectorShape shape);
	ObjectType GetTypeFromShapeAndColor(VectorShape shape, uint32_t color);


};