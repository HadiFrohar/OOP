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
#include "Utilities.h"
#include "Menu.h"
#include "Board.h"
#include "Controller.h"


int main() {
	Board board;
	Menu menuPage(board);
	Controller controller(board, menuPage);

	menuPage.display();

	while (board.isOn())
	{
		if(board.getWindow().isOpen())
			controller.run();
	}

	if(board.getWindow().isOpen())
		board.getWindow().close();

	return EXIT_SUCCESS;
}