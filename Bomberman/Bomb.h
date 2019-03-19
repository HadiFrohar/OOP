#pragma once
#include "screen.h"
class Bomb
{
public:
	Bomb(Position pos); //create bomb
	
	//void setPosition(short row, short col); //set bomb position
	Position getPosition(); //return bomb position

    // check if elemnt in radius of the bomb, if the position got is in the
	//same block or up,down,right,left block it will return true
	bool isInRadius(Position pos);

	//void setTime(); //set bomb time (3)
	void decreaseTime(); //decrease bomb time (-1)
	short getTime(); //return bomb time

private:
	Position m_position; //bomb position
	short m_time; //bomb time left till destroy
};

