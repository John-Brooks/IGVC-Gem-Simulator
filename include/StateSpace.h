#pragma once

#define NUM_SENSORS 12

struct StateSpace
{
	double VehicleSpeed;
	double SteeringAngle;
	bool test_ended = false;
	double reward = 0;
	double distances[NUM_SENSORS];
};