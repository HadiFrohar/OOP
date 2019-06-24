#include "Bushes.h"



Bushes::Bushes(const sf::Vector2f & pos)
	:ImmovableObject(pos, sheetsController->treeWater->getSheets(), sheetsController->treeWater->getData()[0])
{
}

void Bushes::collide(Object * object)
{
	object->collide(this);
}
