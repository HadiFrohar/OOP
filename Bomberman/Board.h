#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Robot.h"
#include "Keyboard.h"
#include "Guard.h"
#include "Settings.h"
#include "Door.h"
#include "Bomb.h"
#include <cstdlib>
#include "Rock.h"

class Board
{
public:
	Board(); //build the board, we also clear the elements just in case
	
	void clear(); //clear board items (map, guards, rocks, bombs)

	void setRobot(Robot robot); //set current robot
	void setSettings(std::vector<std::string> map, int size, int steps); //set level settings
	int getSteps(); //get the steps that left
	//void setSize(int size); //set map size
	//void setSteps(int steps); //set level steps
	//void setMap(std::vector<std::string> map); //set map of board

	//this function reads the elements of the level from the map (robot, guards
	//rocks...) and adds them to the data of the board (vector or one item),
	//and removes them from the map (except for the rocks). it will convert the
	// door to rock and add it to the doors vector
	void readMap();

	//this is the main function to play the game, it will call for the readMap
	//function. this function also prints the map and everything happens, it
	// will give the player to play (move or put a bomb or anything) and lets
	//the guards move, check the bombs. if player finishes the level (reached
	//door it will return true so the games continues for the next level (if
	//there), if the player died, lost the game (steps=0) it will return false.
	//it sets the score to zero, it also prints the status of the robot.
	bool finishLevel();

	void killedGuard(); //adds score for killing a guard (5*num of guards)
	void finishedLevel(); //add score for finished the level (20*num of guards)

	std::vector<Bomb> getBombs(); //return the bombs vector
	void addBomb(Bomb bomb); //add new bomb to the vector
	void removeBomb(size_t i); //remove bomb from the vector
	Robot getRobot(); //returns current robot

private:
	int m_mapSize, //size of the map
		m_steps, //level steps
		m_guardsSize, //size of guards
		m_levelScore; //score of the level
	std::vector<std::string> m_map; //the map
	Robot m_robot; //current robot
	Door m_door; //the door for exiting the level (win)
	std::vector<Guard> m_guards; //the guards
	std::vector<Rock> m_rocks; //the rocks
	std::vector<Bomb> m_bombs; //the bombs

};
 