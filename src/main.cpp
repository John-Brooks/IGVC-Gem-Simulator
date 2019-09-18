#include "Graphics.h"
#include <chrono>
#include <thread>

static Graphics graphics;

int main(int argc, char** argv)
{
	graphics.SetWindowSize(640, 480);
	graphics.Init();
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	graphics.Close();
	return 0;
}