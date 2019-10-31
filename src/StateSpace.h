#pragma once

struct StateSpace
{
	double VehicleSpeed;
	double SteeringAngle;
	bool test_ended = false;
	double reward = 0;
};