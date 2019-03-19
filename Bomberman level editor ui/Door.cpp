#include "Door.h"
#include "Utilities.h"

Door::Door()
	:Object()
{
	setType(DOOR, DOORPATH);
}

void Door::use(const sf::Vector2f & pos)
{
	setPosition(pos);
	m_used = true;
}

void Door::remove()
{
	m_used = false;
}

bool Door::isUsed()
{
	return m_used;
}


