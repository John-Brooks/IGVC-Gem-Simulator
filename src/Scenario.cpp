#include "Scenario.h"
#include "tinyxml2.h"

using namespace tinyxml2;

//RGB
#define LANE_LINE_COLOR 0xFF0000
#define REWARD_GATE_COLOR 0x00FF00
#define END_ZONE_COLOR 0x00FF00
#define START_LOCATION_COLOR 0x00FF00

bool Scenario::ConvertFile(std::string path)
{
	mObjects.clear();
	mStartingLocation = Pose();
	mEndZone = nullptr;
	
	XMLDocument doc;
	doc.LoadFile(path.c_str());

	XMLElement* svg = doc.FirstChildElement("svg");
	if (!svg)
		return false;

	if (!ReadMapSize(svg))
		return false;

	XMLElement* g = svg->FirstChildElement("g");
	while (g)
	{
		const XMLAttribute* transform = g->FindAttribute("transform");
		if (transform) 
			UpdateTranslation(transform->Value());
		else
		{
			mXTranslation = 0;
			mYTranslation = 0;
		}

		if (!ReadPaths(g))
			return false;

		if (!ReadRects(g))
			return false;

		g = g->NextSiblingElement("g");
	}

	return true;
}

bool Scenario::ReadMapSize(XMLElement* svg)
{
	const XMLAttribute* xml_width = svg->FindAttribute("width");
	if (!xml_width)
		return false;
	mWidth = xml_width->DoubleValue();

	const XMLAttribute* xml_height = svg->FindAttribute("height");
	if (!xml_height)
		return false;
	mHeight = xml_height->DoubleValue();

	return true;
}

void Scenario::UpdateTranslation(const std::string& transform)
{
	std::string translate = "translate(";
	long long pos = transform.find(translate, 0);
	if (pos == std::string::npos)
		return;

	translate = transform.substr(translate.length(), transform.length() - translate.length());

	long long comma = translate.find(',', 0);

	std::string str_x1 = translate.substr(0, comma);
	std::string str_y1 = translate.substr(comma + 1, translate.length() - comma - 1);

	mXTranslation = std::stod(str_x1);
	mYTranslation = std::stod(str_y1);
}

Line Scenario::ConvertDimensionToLine(const std::string& dimension)
{
	//format: "m x1,y1 x2,y2"

	//throw away "m "
	std::string coordinates = dimension.substr(2, dimension.length() - 2);
	long long first_comma = coordinates.find(',', 0);
	long long space = coordinates.find(' ', first_comma);
	long long second_comma = coordinates.find(',', space);


	std::string str_x1 = coordinates.substr(0, first_comma);
	std::string str_y1 = coordinates.substr(first_comma+1, space - first_comma - 1);
	std::string str_x2 = coordinates.substr(space+1, second_comma - space - 1);
	std::string str_y2 = coordinates.substr(second_comma+1, coordinates.length() - second_comma -1);


	Point p1, p2;
	p1.x = std::stod(str_x1) + mXTranslation;
	p1.y = std::stod(str_y1) + mYTranslation;
	p2.x = p1.x + std::stod(str_x2);// +mXTranslation;
	p2.y = p1.y + std::stod(str_y2);// +mYTranslation;

	p1.y = mHeight - p1.y;
	p2.y = mHeight - p2.y;

	return Line(p1,p2);
}

Scenario::RGBValue_t Scenario::GetStrokeColorFromStyle(const std::string& style)
{
	RGBValue_t val;
	memset(&val, 0, sizeof(val));
	
	std::string stroke = "stroke:#";

	long long stroke_pos = style.find(stroke);
	if (stroke_pos == std::string::npos)
		return val;

	std::string rgb = style.substr(stroke_pos + stroke.length(), 6);
	val.r = std::stol(rgb.substr(0, 2), 0, 16);
	val.g = std::stol(rgb.substr(2, 2), 0, 16);
	val.b = std::stol(rgb.substr(4, 2), 0, 16);

	return val;
}
Scenario::RGBValue_t Scenario::GetFillColorFromStyle(const std::string& style)
{
	RGBValue_t val;
	memset(&val, 0, sizeof(val));

	std::string stroke = "fill:#";

	long long stroke_pos = style.find(stroke);
	if (stroke_pos == std::string::npos)
		return val;

	std::string rgb = style.substr(stroke_pos + stroke.length(), 6);
	val.r = std::stol(rgb.substr(0, 2), 0, 16);
	val.g = std::stol(rgb.substr(2, 2), 0, 16);
	val.b = std::stol(rgb.substr(4, 2), 0, 16);

	return val;
}

bool Scenario::ConvertPathToLineDrawable(XMLElement* path, ScenarioObject& object)
{
	const XMLAttribute* d = path->FindAttribute("d");
	if (!d)
		return false;

	std::string d_str = d->Value();

	//The path includes arcs which are not supported by this function
	if (d_str.find('a', 0) != std::string::npos)
		return false;

	Line line = ConvertDimensionToLine(d->Value());
	object = ScenarioObject(line);

	const XMLAttribute* style = path->FindAttribute("style");
	if (style)
	{
		RGBValue_t rgb = GetStrokeColorFromStyle(style->Value());
		object.mColor.r = rgb.r;
		object.mColor.g = rgb.g;
		object.mColor.b = rgb.b;
	}
	return true;
}

bool Scenario::PathIsStartLocationMarker(XMLElement* path)
{
	const XMLAttribute* sodipodi_type = path->FindAttribute("sodipodi:type");
	if (!sodipodi_type)
		return false;
	std::string type = sodipodi_type->Value();
	if (type != "arc")
		return false;
	const XMLAttribute* style = path->FindAttribute("style");
	if (!style)
		return false;
	RGBValue_t rgb = GetFillColorFromStyle(style->Value());
	if (rgb.r != 0 || rgb.g != 255 || rgb.b != 0)
		return false;

	return true;
}
bool Scenario::ReadAndSetStartLocation(XMLElement* path)
{
	const XMLAttribute* sodipodi_x = path->FindAttribute("sodipodi:cx");
	const XMLAttribute* sodipodi_y = path->FindAttribute("sodipodi:cy");
	const XMLAttribute* sodipodi_start = path->FindAttribute("sodipodi:start");
	const XMLAttribute* sodipodi_end = path->FindAttribute("sodipodi:end");

	if (!sodipodi_x || !sodipodi_y || !sodipodi_start || !sodipodi_end)
		return false;

	mStartingLocation.pos.x = sodipodi_x->DoubleValue() + mXTranslation;
	mStartingLocation.pos.y = mHeight - (sodipodi_y->DoubleValue() + mYTranslation);

	mStartingLocation.angle = (sodipodi_start->DoubleValue() + sodipodi_end->DoubleValue()) / 2.0;
	return true;
}

bool Scenario::ReadPaths(XMLElement* parent)
{
	XMLElement* path = parent->FirstChildElement("path");
	for(XMLElement* path = parent->FirstChildElement("path"); path != nullptr; path = path->NextSiblingElement("path"))
	{
		ScenarioObject object;
			
		if (PathIsStartLocationMarker(path))
		{
			if (!ReadAndSetStartLocation(path))
				return false;
			continue;
		}

		ConvertPathToLineDrawable(path, object);
		ImportToScenarioObjects(object, VectorShape::Line);
	}
	return true;
}


bool Scenario::ConvertRectToDrawable(XMLElement* xml_rect, ScenarioObject& object)
{
	const XMLAttribute* x = xml_rect->FindAttribute("x");
	const XMLAttribute* y = xml_rect->FindAttribute("y");
	const XMLAttribute* width = xml_rect->FindAttribute("width");
	const XMLAttribute* height = xml_rect->FindAttribute("height");
	if (!x || !y || !width || !height)
		return false;

	Point top_left, bottom_right;

	top_left.x = x->DoubleValue() + mXTranslation;
	top_left.y = mHeight - (y->DoubleValue() + mYTranslation);
	bottom_right.x = x->DoubleValue() + (width->DoubleValue()) + mXTranslation;
	bottom_right.y = mHeight - (y->DoubleValue() + (height->DoubleValue()) + mYTranslation);

	object = ScenarioObject(Rect(top_left, bottom_right));

	const XMLAttribute* style = xml_rect->FindAttribute("style");
	if (style)
	{
		RGBValue_t rgb = GetStrokeColorFromStyle(style->Value());
		object.mColor.r = rgb.r;
		object.mColor.g = rgb.g;
		object.mColor.b = rgb.b;
	}
	return true;
}

bool Scenario::ReadRects(XMLElement* parent)
{
	XMLElement* rect = parent->FirstChildElement("rect");
	while (rect)
	{
		ScenarioObject object;
		ConvertRectToDrawable(rect, object);
		ImportToScenarioObjects(object, VectorShape::Rectangle);
		rect = rect->NextSiblingElement("rect");
	}
	return true;
}

ObjectType Scenario::GetTypeFromShapeAndColor(VectorShape shape, uint32_t color)
{
	switch (shape)
	{
		case VectorShape::Line:
			switch (color)
			{
				case LANE_LINE_COLOR:
					return ObjectType::LaneLine;

				case REWARD_GATE_COLOR:
					return ObjectType::RewardGate;

				default:
					//If we don't have a matching color we will add it as an unknown object.
					return ObjectType::Unknown;
			}
			
		case VectorShape::Rectangle:
			switch (color)
			{
				case END_ZONE_COLOR:
					return ObjectType::EndZone;

				default:
					return ObjectType::Unknown;
			}	

		case VectorShape::Circle:
			return ObjectType::Unknown;

		default:
			return ObjectType::Unknown;
	}
}

bool Scenario::ImportToScenarioObjects(const ScenarioObject& object, VectorShape shape)
{
	uint32_t color = 0;
	color |= object.mColor.r << 16;
	color |= object.mColor.g << 8;
	color |= object.mColor.b;

	ObjectType type = GetTypeFromShapeAndColor(shape, color);

	//Actually create the derived object type. When these objects have their own implementations
	//they should be instantiated here.
	switch (type)
	{
		case ObjectType::LaneLine:
		case ObjectType::RewardGate:
		case ObjectType::Unknown:
			mObjects.push_back(std::make_shared<ScenarioObject>(object));
			break;
		case ObjectType::EndZone:
			mEndZone = std::make_shared<EndZone>(object);
			mObjects.push_back(std::make_shared<ScenarioObject>(object));
			break;
		default:
			return false;
	}

	mObjects.back()->mType = type;
	return true;
}
