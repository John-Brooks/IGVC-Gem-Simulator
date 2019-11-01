#pragma once
#include <stdio.h>
#include "Graphics.h"
#include "Environment.h"
#include "ActionSpace.h"
#include "StateSpace.h"
#include <chrono>
#include <thread>
#include "Scenario.h"

extern "C" void HelloWorld() { printf("Hello World!\n"); }

void run()
{
	Environment env;
	ActionSpace action;
	StateSpace state;
	action.VehicleSpeed = 1;
	action.SteeringAngle = 0.0;
	
	env.LoadScenario("/media/john/5A506552506535C3/Users/John/Desktop/drawing.svg");
	env.SetSimulationTimeStep(0.016);
	int direction = 1;
	while(true)
	{
		action.SteeringAngle += 0.01 * direction;
		if (action.SteeringAngle > M_PI / 4.0 || action.SteeringAngle < M_PI / -4.0)
			direction = direction * -1;

		state = env.Step(action);
		if(!env.Render())
		{
			env.Close();
			return;
		}

		if (state.test_ended)
			env.Reset();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	env.Close();
}

StateSpace Step(ActionSpace action)
{

}
