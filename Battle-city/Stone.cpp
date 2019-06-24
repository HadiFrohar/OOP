#include "Stone.h"


Stone::Stone(const sf::Vector2f & pos)
	:Wall(pos, sheetsController->wall->getSheets(), sheetsController->wall->getData()[1])
{
}

