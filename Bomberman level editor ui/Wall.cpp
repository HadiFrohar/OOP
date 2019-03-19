#include "Wall.h"
#include "Utilities.h"

Wall::Wall(const sf::Vector2f& pos)
	:Object(pos)
{
	setType(WALL, WALLPATH);
}
