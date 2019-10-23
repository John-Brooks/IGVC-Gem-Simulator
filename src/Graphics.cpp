#include "Graphics.h"
#include "SDL.h"
#include <stdio.h>
#include <algorithm>
#include <cmath>

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
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	Line render_line;
	for (auto& drawable : mDrawables)
	{
		SDL_SetRenderDrawColor(mRenderer, drawable->mColor.r, drawable->mColor.g, drawable->mColor.b, drawable->mColor.a);
		for( auto& line : drawable->mLines)
		{ 
			if ( drawable->mPixelCoordinates )
			{
				SDL_RenderDrawLine(mRenderer, line.p1.x, line.p1.y, line.p2.x, line.p2.y);
				continue;
			}
			render_line = line;
			ApplyObjectPose(render_line, drawable->mPose);
			ConvertToScreenCoordinate(render_line);
			
			SDL_RenderDrawLine(mRenderer, render_line.p1.x, render_line.p1.y, render_line.p2.x, render_line.p2.y);
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

void Graphics::ConvertToScreenCoordinate(Line& line)
{
	line.p1.x *= mWindowWidth / mEnvironmentWidth;
	line.p2.x *= mWindowWidth / mEnvironmentWidth; 
	line.p1.y *= mWindowHeight / mEnvironmentHeight;
	line.p2.y *= mWindowHeight / mEnvironmentHeight;

	//invert y-axis from pixel coordinates to regular cartesian.
	line.p1.y = mWindowHeight - line.p1.y;
	line.p2.y = mWindowHeight - line.p2.y;
}

void ApplyObjectAngleToPoint(Point& point, const Pose& pose)
{
	double r, theta;

	r = sqrt(pow(point.y, 2) + pow(point.x, 2));

	theta = CalculatePointAngle(point);
	theta += pose.angle;
	point.x = r * cos(theta);
	point.y = r * sin(theta);
}

void Graphics::ApplyObjectPose(Line& line, const Pose& pose)
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
}