#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Object.h"

#define WALL '#'
#define ROCK '@'
#define DOOR 'D'
#define ROBOT '/'
#define GUARD '!'
#define WHITESPACE ' '
#define NEWLINE '\n'
#define MAPPATH "board.bomb"
#define NOTYPE -1
#define DEFAULT_SIZE 24
#define BUTTON_SIZE 50
#define GAME_Y_POS 72
#define FONTUSED "arial.ttf"
#define ROBOTPATH "robot.png"
#define ROCKPATH "rock.png"
#define GUARDPATH "guard.png"
#define WALLPATH "wall.jpg"
#define DOORPATH "door.png"
#define TRASHPATH "trash.jpg"
#define EMPTYALLPATH "emptyall.jpg"




//reads the map from the file (if there) and adds it to vector of strings
std::vector<std::string> getMap(std::fstream &file, int &size, int &steps);
//creates empty map (only walls) to make it easier for the user
std::vector<std::string> createEmptyMap(int size);
//update the elemtns of the map in the file
void updateMapInFile(std::vector<std::string> map, int size, int steps);
//creates shape of mouse over of the elemnt for SFML
sf::RectangleShape createOverShape(const sf::Vector2f& pos, std::string imgPath);
//checks if an element on a point
bool hasPoint(std::vector<Object> objects, const sf::Vector2f& pos);
//writes all items of a specfic element on the map
void writeOnMap(std::vector<std::string> &map, std::vector<Object> objects);
//writes one element on the map
void writeOnMapChar(std::vector<std::string>& map, const sf::Vector2f &pos, char c);

//enums for the types
enum type
{
	robotType = 0,
	guardType = 1,
	rockType = 2,
	doorType = 3,
	wallType = 4,
	removeType = 5,
	emptyAll = 6
};