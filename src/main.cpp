#include "Graphics.h"
#include "Environment.h"
#include "ActionSpace.h"
#include <chrono>
#include <thread>


static Graphics graphics;

int main(int argc, char** argv)
{
	Environment env;
	ActionSpace action;
	action.VehicleSpeed = 2;
	action.SteeringAngle = 0.5;

	env.Init();
	env.SetSimulationTimeStep(0.016);
	while(true)
	{
		env.Step(action);
		env.Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	graphics.Close();
	return 0;
}