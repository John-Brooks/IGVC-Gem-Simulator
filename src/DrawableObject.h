#pragma once

#include "Geometry.h"
#include "SDL.h"


class DrawableObject : public Object {
public:
	DrawableObject() : mPixelCoordinates(false) {}

	struct Color
	{
		Color() : r(255), g(255), b(255), a(255) {}
		int r, g, b, a;
		
	} mColor;

	bool mPixelCoordinates;
};