#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Robot: public Object
{
public:
	Robot(); //creates robot
	void use(const sf::Vector2f& pos); //makes the robot used and updates pos
	void remove(); //removes the robot (m_usued = false)
	bool isUsed(); //checks if the robot is used


private:

	bool m_used = false; //robot used
};