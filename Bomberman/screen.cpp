#include "screen.h"

#include <Windows.h>

void moveCursor(const Position & pos)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { pos.col, pos.row });
}
