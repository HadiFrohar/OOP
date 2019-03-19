#pragma once
#include <vector>
#include <string>
#include "Robot.h"
#include "Guard.h"
#include <sstream>

#define START_LIFE 3
#define EMPTY 0
#define WALL '#'
#define ROCK '@'
#define DOOR 'D'
#define ROBOT '/'
#define ROBOT_ON_BOMB '%'
#define GUARD '!'
#define WHITESPACE ' '
#define DESTROYED '*'

//gets the settings of the map, it will get the first line of the level
void getSettings(std::string firstLine, int &size, int &steps);

//checks if any guard and robot is on the same block
bool hasGuardRobot(std::vector<Guard> guards, Robot robot);
//moves the guards, it has 4 conidtions, it chooses one randomally, each one
//has 2 conditions, it will check if the robot can move, if not it will go for
//the second condition and check if can move, if also no then the guard will
//not move. the moves are based on robot position (Check conditions)
void guardsMove(std::vector<std::string>map, std::vector<Guard> &guards, Robot robot);
//void clearGuards(std::vector<std::string>&map, std::vector<Guard> guards);

//it will decrease all the bombs time by 1
void decreaseBombsTime(std::vector<Bomb> &bombs);
//it will remove destroyed bombs
void checkBombs(std::vector<Bomb> &bombs);
//it will check if the block has bomb
bool hasBomb(std::vector<Bomb> bombs, Position pos);