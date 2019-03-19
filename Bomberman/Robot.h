#pragma once
#include "screen.h"
#include "Keyboard.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include "Bomb.h"
#include "Door.h"


class Robot
{
public:
	Robot(); //creats the robot with 0 score and 3 life

	void setPosition(short row, short col); //sets robot position
	Position getPosition(); //returns robot position
	bool isUp(Position pos); //checks if robot position is up
	bool isRight(Position pos); //checks if robot position is down

	void DecreaseLife(); //decreases 1 from robot life
	int getLife(); //returns robot life

	bool canMove(char c); //checks if robot can move to specific block
	//this function will wait for the player to enter a key, if the key is not
	//recgonized it will return to the same function, if he enters arrow keys
	//it will check if the robot can move to t he wanted direction (left up down
	//right) if yes it will move the robot (change its position). if player
	//enters space he will lose his turn, (steps -1), if he enters small b it
	//will put a bomb in the block of the robot. if player pressed any arrow key
	//or space it will return true (to decrease steps) if entered small b it
	//will return false
	bool moveRobot(std::vector<std::string> map, std::vector<Bomb> &bombs);

	bool onBomb(std::vector<Bomb> bombs); //checks if robot is on bomb
	bool bombDamage(Bomb bomb); //checks if robot is in bomb radius


	int getScore(); //returns robot score
	void addScore(int score); //adds score

	bool win(Door door); //returns true if the robot is on door block (win)

private:
	int m_life, //robot life
		m_score; //robot score
	Position m_position; //robot position
};

