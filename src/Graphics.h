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
		
		void SetEnvironmentWidth(const double& new_width) { mEnvironmentWidth = new_width; }
		void SetEnvironmentHeight(const double& new_height) { mEnvironmentHeight = new_height; }

    private:
		void ConvertToScreenCoordinate(Line& line);
		void ApplyObjectPose(Line& line, const Pose& pose);

		SDL_Window* mWindow = NULL;
		SDL_Renderer* mRenderer = NULL;
		SDL_Surface* mScreenSurface = NULL;

		std::vector< const DrawableObject* > mDrawables;

		int mWindowWidth;
		int mWindowHeight;

		double mEnvironmentWidth;
		double mEnvironmentHeight;


};
