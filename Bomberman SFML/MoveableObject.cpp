#include "MoveableObject.h"




MoveableObject::MoveableObject()
	:m_shapeType(0), m_movement(LEFT)
{
}

MoveableObject::MoveableObject(const sf::Vector2f & pos, const sf::Texture& sheets)
	:Object(pos, sheets), m_shapeType(0), m_movement(LEFT)
{
}

bool MoveableObject::canMove(std::vector<std::unique_ptr<Object>> &staticObjects)
{
	for (size_t i = 0; i < staticObjects.size(); i++)
		if (collision(staticObjects[i]->getShape()))
			return false;
	return true;
}

bool MoveableObject::isInBoomRange(std::vector<Bomb>& bombs)
{
	for (auto bomb : bombs)
		if (!bomb.isBoomed())
			continue;
		else if (bomb.isInRange(getShape()))
			return true;

	return false;
}

