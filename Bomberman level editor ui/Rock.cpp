#include "Rock.h"
#include "Utilities.h"

Rock::Rock(const sf::Vector2f& pos)
	:Object(pos)
{
	setType(ROCK, ROCKPATH);
}

