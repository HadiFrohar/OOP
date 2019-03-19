#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Guard : public Object
{
public:
	Guard(const sf::Vector2f& pos); //creates guard
};