#pragma once
#include "screen.h"
#include <vector>
#include <string>
#include <time.h>
#include "Bomb.h"

#define WALL '#'
#define ROCK '@'
#define DOOR 'D'

class Guard
{
public:
	Guard(); //create guard

	void setPosition(short row, short col); //set guard position
	Position getPosition(); //return guard position

	void moveUp(); //move guard up
	void moveDown(); //move guard down
	void moveLeft(); //move guard left
	void moveRight(); //mvoe guard right
	//returns if can move to a specific block (false for wall, rock, door)
	bool canMove(char c);

	bool onBomb(std::vector<Bomb> bombs); //returns if guard is in bomb radius

private:
	Position m_position; //guard position
};