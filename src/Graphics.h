#pragma once
#include "SDL.h"
#include "Drawable.h"
#include <vector>

class Graphics {
    public:
		void SetWindowSize(const int& width, const int& height) { mWindowWidth = width; mWindowHeight = height; }
        //void SetDrawables(const std::vector< Drawable > drawables );
		bool Init();
		void Close();
        bool Render();


    private:
		SDL_Window* gWindow = NULL;
		SDL_Surface* gScreenSurface = NULL;

		int mWindowWidth;
		int mWindowHeight;


};
