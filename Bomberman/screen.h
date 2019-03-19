#pragma once

struct Position
{
	short row;
	short col;
};

void moveCursor(const Position& pos);