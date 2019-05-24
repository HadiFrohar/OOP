#pragma once
#include <SFML/Graphics.hpp>

class ColorRectangle
{
public:
	ColorRectangle() = default;
	ColorRectangle(const sf::Color & usedColor, const sf::Vector2f & pos, const float size);
	void enable(); //enables color button, if it is enabled the user can play with this color
	void disable(); //disable color button

	bool enabled(); //returns color button state
	sf::RectangleShape & getShape(); //returns rectangle

private:
	sf::RectangleShape m_rectangle;
	sf::Color m_usedColor; //used color = the color
	sf::Color m_unusedColor; //its black, (just in case we want to use any other color to state that the button is disabled)
};

