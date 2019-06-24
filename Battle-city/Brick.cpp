#include "Brick.h"




Brick::Brick(const sf::Vector2f &pos)
	:Wall(pos, sheetsController->wall->getSheets(), sheetsController->wall->getData()[0])
{
}
