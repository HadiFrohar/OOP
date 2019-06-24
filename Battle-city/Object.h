#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "SheetsController.h"
class Bullet;
class Wall;
class Water;
class Basement;

class Object
{
public:
	Object(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect);
	virtual ~Object() = 0 {};

	virtual void draw(sf::RenderWindow* window); //draws object
	static bool collision(const Object* object1, const Object* object2); //checks if objects intersects
	virtual void collide(Object* object) = 0; //normally calls for object.collideWith(this)
	virtual void collideWith(Object* object) {} //collision with object effect (normally nothing)
	virtual void collideWith(Bullet* bullet) {} //collision with bullet effect
	virtual void collideWith(Wall* wall) {} //collision with wall effect
	virtual void collideWith(Basement* basement) {} //collision with basement effect
	virtual void collideWith(Water* water) {} //collision with water effect


	static void updateSheetsController(SheetsController *controller); //game sheets controller updater

	const sf::FloatRect getGlobalBounds() const; //returns sprite global bounds rect
	const sf::Vector2f getPosition() const; //returns sprite position


protected:

	static SheetsController *sheetsController; //game sheets controller
	static bool isOutsideGameBoard(const Object *object, sf::RectangleShape* gameBoard); //checks of object is outside game bounds

	sf::Sprite m_sprite; //object sprite
};

