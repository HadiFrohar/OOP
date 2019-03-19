#pragma once

#include <SFML/Graphics.hpp>

class Object
{
public:
	//creates an object
	Object();
	//creates an object from position and font
	Object(const sf::Vector2f& pos);
	//draws object on SFML window
	void draw(sf::RenderWindow& window);
	//check if clicked on the object
	bool click(const sf::Vector2f& pos);
	//updates object position
	void setPosition(const sf::Vector2f& pos);
	//returns object position
	sf::Vector2f getPosition();
	//updates object type (guard, robot, door...)
	void setType(char type, std::string imgPath);
	//returns object type (guard, robot, door...)
	char getType();
	//states that the mouse is over the object
	void mouseOver();
	//states that the mouse is not over the object
	void mouseNotOver();
	//returns the state (map is over the element or not)
	bool isMouseOver();




private:
	sf::RectangleShape createShape() const; //creates button shape
	sf::Vector2f m_position{ 0, 0 }; //object position
	sf::Texture m_texture; //the image in the button
	std::string m_imgPath; //path of the img
	char m_type; //object type (guard, robot, door...)
	bool m_mouseOver = false; //states if map is over an element
};