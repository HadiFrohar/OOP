#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Wall : public Object
{
public:
	Wall(const sf::Vector2f& pos); //creates wall
};