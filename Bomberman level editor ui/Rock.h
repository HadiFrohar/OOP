#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Rock : public Object
{
public:
	Rock(const sf::Vector2f& pos); //creates rock
};