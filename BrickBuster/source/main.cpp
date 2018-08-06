#include "Engine.h"
#include "GameException.h"
#include <iostream>

int main(int, char**)
{
	Engine engine;
	try
	{
		engine.run();
	}
	catch (GameException e)
	{
		std::cerr << "Exception while running engine." << std::endl;
		std::cerr << "Error is: " << e.getErrorMsg() << std::endl;
		std::cerr << "Exiting application";
	}

    return 0;
}