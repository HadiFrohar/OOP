#pragma once
#include "screen.h"
class Door
{
public:
	Door(); //create door
	
	void setPosition(short row, short col);//set door pos
	Position getPosition(); //return door pos
	//bool isHidden(); //check if door hidden

private:
	Position m_position; //door position
	//bool m_hidden; //is door hidden
};

