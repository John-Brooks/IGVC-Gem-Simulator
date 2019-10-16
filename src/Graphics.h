#pragma once
#include "SDL.h"

#include <vector>
#include "Geometry.h"

class DrawableObject;
class Rect;

class Graphics {
    public:
		void SetWindowSize(const int& width, const int& height) { mWindowWidth = width; mWindowHeight = height; }
		bool Init();
		void Close();
        bool Render();

		void AddDrawableObject(const DrawableObject* obj);
		void RemoveDrawableObject(const DrawableObject* obj);
		void ClearDrawableObjects();

    private:
		Point ConvertToScreenCoordinate(const Point& point);

		SDL_Window* mWindow = NULL;
		SDL_Renderer* mRenderer = NULL;
		SDL_Surface* mScreenSurface = NULL;

		std::vector< const DrawableObject* > mDrawables;

		int mWindowWidth;
		int mWindowHeight;

		double mEnvironmentWidth;
		double mEnvironmentHight;


};
