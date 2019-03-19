#pragma once

#include <iostream>
#include <fstream>
#include "Button.h"
#include <Windows.h>
#include <sstream>
#include "Guard.h"
#include "Wall.h"
#include "Robot.h"
#include "Robot.h"
#include "Door.h"
#include "Rock.h"

#include <SFML/Graphics.hpp>
#include <experimental/vector>

class Controller
{
public:
	Controller();

	//This function is the main function of the (level creator), it will read
	//the file of the map, (if there) and then it will give the user to create
	//the map he wants and update it. if there is no file it will create one
	//and ask the user to enter the size of the map and steps of the map and
	//then creates empty map, then it will give the user to create the map he
	//wants
	void run();

	//creates the buttons of the game (types\remove)
	void createButtons();

	//clears all elemnts (their vectors)
	void clearElements();

	//reads the elemtents of the map from vector of strings, it will call for
	//clearElements function and then updates the new elements by reading the
	//strings
	void readElements();

	//update elements on the file, it will remove everything in the file and
	//clears the vector of the strings (the map) then update the elemtns on it
	//then it will call for a function to write the map on the file.
	void updateElements();

	//checks if place is taken by an element
	bool placeIsTaken(sf::Vector2f pos);

	//creates new map, it will get from the user the size and stpes and then call
	//for updateElements function
	void newMap();

	//checks if the mosue over an element when we want to remove elements
	void checkMouseOver(sf::Vector2f pos);
	
	//unhover all elements
	void unhoverElements(const sf::Vector2f & pos);

	//draws lines on the window to make it easier for the user (makes indexes)
	void drawLines();



private:
	void HandleEvents();
	void draw(); //draws an object on the SFML window
	//void click(const sf::Vector2f& pos);

	//check if clicked on the map to update the elements in the file
	bool click(sf::Vector2f pos);

	sf::RenderWindow m_window;
	std::vector<Button> m_buttons;

	
	HWND m_cmdWND; //command window
	std::fstream m_file; //the file used for the map (board.bomb)

	std::vector<Wall> m_walls; //walls vector
	std::vector<Guard> m_guards; //guards vector
	std::vector<Rock> m_rocks; //rocks vector
	Robot m_robot; //robot
	Door m_door; //door

	sf::Font m_font; //font used to print on the map

	bool m_newFile; //using new file
	int m_type; //type of button pressed

	sf::Text m_mouseText; //for mouse over

	std::vector<std::string> m_map; //after reading an level we put it in this vector

	int m_size, //size of map NXN
		m_steps; //steps of map
};

