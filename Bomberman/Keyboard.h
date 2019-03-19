 #pragma once

const int SPECIAL_KEY = 224;

// special keys
const int KB_UP = 72;
const int KB_DOWN = 80;
const int KB_LEFT = 75;
const int KB_RIGHT = 77;
const int KB_SPACE = 32;
const int KB_SMALLB = 98;

namespace Keyboard
{
	// Implements the same semantics as _getch() from conio.h
	// Currently, handles only regular keys (ASCII values)
	// and arrow keys
	int getch();
};

