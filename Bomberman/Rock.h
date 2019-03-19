#pragma once
#include "screen.h"
#include "Bomb.h"
#include<vector>
class Rock
{
public:
	Rock(Position pos); //creates the rock

	Position getPosition(); //returns rock position

	//bool isBombed();
	//void destroy();
	
	//checks if rock is in bomb radius
	bool inBombRadius(std::vector<Bomb> bombs);

private:
	Position m_position; //rock position
	//bool m_onScreen;
};

