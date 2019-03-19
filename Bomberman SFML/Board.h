#pragma once
#include "Guard.h"
#include "Wall.h"
#include "Robot.h"
#include "Robot.h"
#include "Door.h"
#include "Rock.h"
#include "Bomb.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <time.h>
class Board
{
public:
	Board(); //creates the board, the board has all the window, view and drawing settings

	//draws the elements on the window
	void draw(std::vector<std::unique_ptr<Object>> &staticObjects, std::vector<Guard> &guards, Robot &robot, Door &door, std::vector<Bomb> &bombs, std::vector<Box> &statusBar);
	void clear(); //clears the window and draws the background on it

	//adjusts the size of the window, if the size of the map is bigger than the max window size then it will
	//adjust the size as maximum window size
	void adjustSize(unsigned int size, bool menu);
	float getSize(); //gets the size of the window
	void moveView(int direction); //moves the view on the window
	void adjustView(Robot &robot);

	sf::View & getView(); //returns the view

	bool isOn(); //returns if the window stills on

	void loadResc(); //loads the resources (sheets, fonts)

	void newBackground(); //radnom number generator, used for multiple background


	sf::RenderWindow & getWindow(); //returns the window
	sf::Texture &getSheets(); //returns the loaded sheets
	sf::Font &getFont(); //returns the loaded font
	sf::Image &getIcon(); //returns the loaded icon

private:
	sf::RenderWindow m_window; //main window
	sf::Texture m_sheets; //sheets of the objects
	sf::Font m_font; //font used in the game

	sf::Image m_backgroundSheet; //stores the background sheets
	sf::Texture m_backgroundImg; //texture to draw the background
	sf::Sprite m_background; //the background to draw on the window
	sf::Image m_icon; //icon of the game

	sf::View m_view; //view of the window, used for big maps

	float m_size; //font size

	int m_backgroundPos;

};

