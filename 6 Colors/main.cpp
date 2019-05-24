#ifdef _DEBUG
#pragma comment ( lib , "sfml-main-d.lib" )
#pragma comment ( lib , "sfml-system-d.lib" )
#pragma comment ( lib , "sfml-window-d.lib" )
#pragma comment ( lib , "sfml-graphics-d.lib" )
#elif defined (NDEBUG)
#pragma comment ( lib , "sfml-main.lib" )
#pragma comment ( lib , "sfml-system.lib" )
#pragma comment ( lib , "sfml-window.lib" )
#pragma comment ( lib , "sfml-graphics.lib" )
#else
#error "Unrecognized configuration!"
#endif

#include "SFML/Graphics.hpp"
#include "Controller.h"
#include <iostream>

int main()
{
	try
	{
		Controller controller;
		controller.run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
