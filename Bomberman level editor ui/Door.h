#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Door : public Object
{
public:
	Door(); //creates door
	void use(const sf::Vector2f& pos); //makes the door used and updates its pos
	void remove(); //unuse the door, removes it
	bool isUsed(); //checks if the door is used

private:

	bool m_used = false; //door used
};