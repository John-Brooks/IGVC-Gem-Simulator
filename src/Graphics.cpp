#include "Graphics.h"
#include "SDL.h"
#include "DrawableObject.h"
#include <stdio.h>
#include <algorithm>

bool Graphics::Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		SDL_CreateWindowAndRenderer(mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN, &mWindow, &mRenderer);

		if (mWindow == NULL || mRenderer == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			mScreenSurface = SDL_GetWindowSurface(mWindow);
		}
	}

	return success;
}
void Graphics::Close()
{
	//Destroy window
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
bool Graphics::Render()
{
	Point p1, p2; 
	for (auto& drawable : mDrawables)
	{
		for( auto& line : drawable->lines)
		{ 
			p1 = ConvertToScreenCoordinate(line.p1);
			p2 = ConvertToScreenCoordinate(line.p2);
			SDL_RenderDrawLine(mRenderer, p1.x, p1.y, p2.x, p2.y);
		}
	}
	SDL_RenderPresent(mRenderer);
	return true;
}

void Graphics::AddDrawableObject(const DrawableObject* obj) 
{ 
	mDrawables.push_back(obj); 
}
void Graphics::RemoveDrawableObject(const DrawableObject* obj)
{
	auto iterator = std::find(mDrawables.begin(), mDrawables.end(), obj);
	if (iterator != mDrawables.end())
	{
		mDrawables.erase(iterator);
	}
}
void Graphics::ClearDrawableObjects()
{
	mDrawables.clear();
}

Point Graphics::ConvertToScreenCoordinate(const Point& point)
{
	return Point(point.x / mEnvironmentWidth, point.y / mEnvironmentHight);
}