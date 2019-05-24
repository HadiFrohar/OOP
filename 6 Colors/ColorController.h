#pragma once
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ColorController
{
public:
	ColorController();
	const sf::Color &getRandomColor() const; //returns random color (no-hover type)

	const unsigned int id(const std::pair<sf::Color, sf::Color> &color) const; //returns id of pair
	const unsigned int id(const sf::Color &color) const; //returns id of color (no-hover type)
	const std::pair<sf::Color, sf::Color> &getColor(const int &id) const;  //returns color (no-hover type)
	const std::pair<sf::Color, sf::Color> &getPair(const sf::Color &color) const; //returns pair of colors (color, hoverColor)

	const int getNumOfcolors() const; //returns the amount of colors in game


private:
	std::vector<std::pair<sf::Color, sf::Color>> m_colors; //game colors (pairs - color,hoverColor)
};

