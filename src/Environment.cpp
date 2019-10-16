#include "Environment.h"


void Environment::Init()
{
	Pose vehicle_pose;
	vehicle_pose.pos.x = 50;
	vehicle_pose.pos.y = 50;
	vehicle_pose.angle = 0;

	mVehicle.SetPose(vehicle_pose);

	mGraphics.SetWindowSize(640, 480);
	mGraphics.Init();
	
	mVehicle.GetDrawable();

	mGraphics.AddDrawableObject(mVehicle.GetDrawable());
}

void Environment::Render()
{
	mGraphics.Render();
}