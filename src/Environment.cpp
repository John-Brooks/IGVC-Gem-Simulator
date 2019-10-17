#include "Environment.h"


void Environment::Init()
{
	Pose vehicle_pose;
	vehicle_pose.pos.x = 5;
	vehicle_pose.pos.y = 5;
	vehicle_pose.angle = 0;

	mVehicle.SetPose(vehicle_pose);

	mGraphics.SetEnvironmentWidth(20.0);
	mGraphics.SetEnvironmentHeight(20.0 * (480.0 /640.0));
	mGraphics.SetWindowSize(640, 480);
	mGraphics.Init();

	mGraphics.AddDrawableObject(mVehicle.GetVehicleDrawable());
}

void Environment::Render()
{
	Pose pose = mVehicle.GetPose();
	pose.angle += 0.01;
	mVehicle.SetPose(pose);
	mGraphics.Render();
}