#pragma once
#include "Wall.h"
class Brick : public Wall
{
public:
	Brick(const sf::Vector2f &pos); //passes brick IntRect to wall constructor
};

