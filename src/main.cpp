#include "Graphics.h"
#include "Environment.h"
#include "ActionSpace.h"
#include "StateSpace.h"
#include <chrono>
#include <thread>
#include "Scenario.h"

static Graphics graphics;

int main(int argc, char** argv)
{
	Scenario scen;

	scen.ConvertFile("/media/john/5A506552506535C3/Users/John/Desktop/drawing.svg");

	Environment env;
	ActionSpace action;
	StateSpace state;
	action.VehicleSpeed = 1;
	action.SteeringAngle = 0.0;
	
	env.LoadScenario(&scen);
	env.SetSimulationTimeStep(0.016);
	int direction = 1;
	while(true)
	{
		action.SteeringAngle += 0.01 * direction;
		if (action.SteeringAngle > M_PI / 4.0 || action.SteeringAngle < M_PI / -4.0)
			direction = direction * -1;

		state = env.Step(action);
		env.Render();

		if (state.test_ended)
			env.Reset();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	graphics.Close();
	return 0;
}