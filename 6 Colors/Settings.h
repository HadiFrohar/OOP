#pragma once
#include <string>
#include "SFML/Graphics.hpp"

const unsigned int WINDOWSIZE = 700; //window size
const std::string GAMEFONT = "rc/SEGA.ttf"; //sega font path
const std::string REGULARFONT = "rc/arial.ttf"; //sega font path

const sf::Color BACKGROUNDCOLOR = sf::Color(153, 153, 153, 60); //grey color
const sf::Color BLACK = sf::Color::Black;
const sf::Color WHITE = sf::Color::White;


//color ids
enum Color {
	RED = 0,
	ORANGE = 1,
	YELLOW = 2,
	GREEN = 3,
	BLUE = 4,
	PINK = 5
};




const unsigned int FONT_SIZE = 16;
const float RECTANGLE_SIZE = 40; //color button size
const float SHAPE_SIZE = 30;

//different scales, just in case we change window size
const double BOARD_SCALE = 0.9;
const double TEXT_POS_SCALE = 0.8;
const double COLOR_RECT_SCALE = 0.4;



//down left shape position (user start shape)
const sf::Vector2f DOWN_LEFT = { (float)((1 - BOARD_SCALE) / 2 * WINDOWSIZE),
		(float)((0.99 - BOARD_SCALE)*WINDOWSIZE + BOARD_SCALE * WINDOWSIZE - SHAPE_SIZE) };

//top right shape position (computer start shape)
const sf::Vector2f TOP_RIGHT = { (float)((1 - BOARD_SCALE) / 2 * WINDOWSIZE + BOARD_SCALE * WINDOWSIZE - SHAPE_SIZE),
		(float)(0.99 - BOARD_SCALE)*WINDOWSIZE };