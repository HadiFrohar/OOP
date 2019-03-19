#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"



class Object
{
public:
	Object(); //Object constructor
	Object(const sf::Vector2f & pos, const sf::Texture& sheets); //Object constructor with arguments
	virtual ~Object() = 0 {}; //Used so we can't create an direct Object

	void draw(sf::RenderWindow& window); //draws the object on the window

	void setPoisiton(const sf::Vector2f& pos); //sets the position of the object
	sf::Vector2f getPosition(); //returns the position of the object
	sf::Vector2f& getPositionAsRef(); //returns the position of the object as referecne

	//sets the type of the object, it will set the position of object image in the sheets, and its type.
	void setType(char type, sf::IntRect imgPos);
	void setSheets(sf::Texture& sheets); //passes the sheets to the object
	sf::Texture &getSheets(); //returns the sheets that the object has
	char &getType(); //returns type of the object
	void setImgPos(sf::IntRect imgPos); //updates the position of object image in the sheets
	bool collision(sf::Sprite sprite); //checks if there is an coliision with passed object
	void setSize(float size); //updates the size of the object (scale)

	//returns object shape, this function is used for collision, it returns an smaller object
	sf::Sprite &getShape();

private:
//	sf::Sprite createShape() const; //creates button shape
	void createShape(); //creates the shape, it will update the texture, size, posotion and sacle of the sprite
	sf::Vector2f m_position{ 0, 0 }; //object position
	sf::Texture m_sheets; //sheets of the game (sprites images)
	sf::IntRect m_imgPos; //posiiton of the object image in the sheets
	sf::Sprite m_shape; //object shape sprite

	char m_type; //object type (guard, robot, door...)
	float m_size; //size of the object

};

