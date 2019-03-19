#include "Guard.h"
#include "Utilities.h"

Guard::Guard(const sf::Vector2f& pos)
	:Object(pos)
{
	setType(GUARD, GUARDPATH);
}


