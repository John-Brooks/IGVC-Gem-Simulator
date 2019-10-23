#include "Graphics.h"
#include "Environment.h"
#include "ActionSpace.h"
#include <chrono>
#include <thread>
#include "Scenario.h"

static Graphics graphics;

int main(int argc, char** argv)
{
	Scenario scen;

	scen.ConvertFile("c:\\drawing.svg");

	Environment env;
	ActionSpace action;
	action.VehicleSpeed = 1;
	action.SteeringAngle = 0.0;
	
	env.Init(&scen);
	env.SetSimulationTimeStep(0.016);
	int direction = 1;
	while(true)
	{
		action.SteeringAngle += 0.01 * direction;
		if (action.SteeringAngle > M_PI / 4.0 || action.SteeringAngle < M_PI / -4.0)
			direction = direction * -1;

		env.Step(action);
		env.Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	graphics.Close();
	return 0;
}