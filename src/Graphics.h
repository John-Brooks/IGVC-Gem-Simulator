#pragma once
#include "SDL.h"

#include <vector>
#include "Geometry.h"

class DrawableObject;
class Rect;

class Graphics {
    public:
		void SetWindowSize(int width, int height) { mWindowWidth = width; mWindowHeight = height; }
		bool Init();
		void Close();
        bool Render();

		void AddDrawableObject(const DrawableObject* obj);
		void RemoveDrawableObject(const DrawableObject* obj);
		void ClearDrawableObjects();
		
		void SetEnvironmentWidth(double new_width) { mEnvironmentWidth = new_width; }
		void SetEnvironmentHeight(double new_height) { mEnvironmentHeight = new_height; }

    private:
		void ConvertToScreenCoordinate(Line& line);

		SDL_Window* mWindow = NULL;
		SDL_Renderer* mRenderer = NULL;
		SDL_Surface* mScreenSurface = NULL;

		std::vector< const DrawableObject* > mDrawables;

		int mWindowWidth;
		int mWindowHeight;

		double mEnvironmentWidth;
		double mEnvironmentHeight;


};
