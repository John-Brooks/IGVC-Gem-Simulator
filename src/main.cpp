#include "Graphics.h"
#include "Environment.h"
#include <chrono>
#include <thread>


static Graphics graphics;

int main(int argc, char** argv)
{
	Environment env;

	env.Init();
	env.Render();

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	graphics.Close();
	return 0;
}