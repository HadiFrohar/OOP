#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "Guard.h"
#include "Wall.h"
#include "Guard.h"
#include "Wall.h"
#include "Robot.h"
#include "Door.h"
#include "Rock.h"
#include "Board.h"
#include <fstream>
#include "Box.h"
#include <memory>
#include "Menu.h"
#include "LevelMap.h"


class Controller
{
public:
	Controller(Board &board, Menu &menuPage); //Controller constructor
	~Controller(); //Controller destructor
	
	//load resources (loads levels file, loads the sheets and font from the board)
	void loadResc();

	//runs the game, this function does all the game functions, it will read the settings
	//of the level, and then calls for another function to read the map of the level (from the file)
	//and stores the map, then it will read the elements from the map then it will call for a function
	//to finish the level that will returns if the level is finished or not, if it is not finished
	//(player didn't finish in time), it will give the player to play it again (if still alive),
	//if it finished then it will give the player another level, if the robot is died or there
	//is no more levels then it will get out of the funciton.
	void run();
	
	//this function reads the elements from the stored vector of strings, before reading it will call for
	//another function to clear the elements that are stored
	void readItemsFromMap();


	//this function clears the stored elements (include stored map)
	void clearItems();

	//this function is the play-level function, this function will check first if the map is valid (otherwise
	//it will return that the level has finished and states that the map is not valid), then it will call for
	//Board function to adjust the size of the window, then it will adjust the view to be on the robot and 
	//gives the robot to start playing, we keep moving the guards, giving the ability for the player to mvoe 
	//the robot and we check the bombs.
	bool finishedLevel();


	//this function moves the guard
	void moveGuards();

	//this function checks the bombs (if need to boom or remove it if finished)
	void checkBombs(std::vector<Bomb>& bombs);

	//this function checks if the player in robot\bomb range (to damage the robot or not)
	void checkDamage();

	//this two functions are for the status bar (life, score, bombs, time)
	void createStatusBar(); //creates it
	void updateStatusBar(); //updates the status bar each time



private:

	sf::Clock m_clock; //clock used for the game
	sf::Event m_event; //event of the window


	sf::Clock m_pausedClock; //clock used for the paused time (if player want to pause the game)
	sf::Time m_pausedTime;

	void HandleEvents(); //handle events, to quit the game or pause it.
	void draw(); //draws all the objects on the SFML window

	Board &m_board; //the board of the game (drawing class)
	Menu &m_menuPage; //menu page
	sf::Texture m_sheets; //sheets of the spirtes


	std::vector<Guard> m_guards; //guards vector
	Robot m_robot; //robot
	Door m_door; //door
	std::vector<Bomb> m_bombs; //bombs vector

	std::vector<std::unique_ptr<Object>> m_staticObjects; //static objects like rock and wall vector


	std::vector<Box> m_statusBar; //status bar vector, it contains the items in the status bar

	sf::Font m_font; //font used in the game

	//sf::SoundBuffer m_boomSound; //sound of the bomb

	LevelMap map; //map reader
	std::vector<std::string> m_map; //vector that contains the map

	unsigned int m_size, //size of map NXN
		m_levelTime, //max time for the level
		m_bombsCount; //bombs count of the level

	int m_levelScore, //score of the level
		m_guardsSize; //size of the guards

};

