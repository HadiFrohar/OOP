#pragma once
#include "Object.h"
#include "Bomb.h"

class MoveableObject : public Object
{
public:
	MoveableObject(); //Moveable object constructor
	~MoveableObject() {} //Moveable object destructor
	MoveableObject(const sf::Vector2f & pos, const sf::Texture& sheets);

	//checks if the object can move to a specfic place (if there is rock or wall in this place)
	bool canMove(std::vector<std::unique_ptr<Object>> &staticObjects);

	bool isInBoomRange(std::vector<Bomb> &bombs);

	//movement timer (so we don't get different speed)
	sf::Clock m_movementClock;
	sf::Time m_movementTime;

	//animation timer (so we get a good animations)
	sf::Clock m_animationClock;
	sf::Time m_animationTime;

	int m_shapeType; //shape type of the movement (which image of the movement)

	enum movmentType {
		RIGHT,
		LEFT,
		DOWN,
		UP
	};

	int m_movement; //movement direction

private:
	virtual void moveLeft() = 0; //moves left (if possible) and it will change movement direction
	virtual void moveRight() = 0; //moves right (if possible) and it will change movement direction
	virtual void moveDown() = 0; //moves down (if possible) and it will change movement direction
	virtual void moveUp() = 0; //moves up (if possible) and it will change movement direction
	virtual void updateAnimation() = 0; //updates the animations
};

