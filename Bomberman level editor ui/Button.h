#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(const sf::Vector2f& pos, std::string image); //creates button
	void draw(sf::RenderWindow& window); //draws the button on SFML window
	bool click(const sf::Vector2f& pos); //checks if clicked on the button
	void unclick(); //unborder the botton

private:
	sf::RectangleShape createShape() const; //creates button shape
	bool clicked = false; //is button clicked (for border)
	sf::Texture m_texture; //the image in the button

	sf::Vector2f m_position{ 0, 0 }; //button position
};

