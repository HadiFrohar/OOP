#include "Robot.h"
#include "Utilities.h"

Robot::Robot()
	:Object()
{
	setType(ROBOT, ROBOTPATH);
}


void Robot::use(const sf::Vector2f & pos)
{
	setPosition(pos);
	m_used = true;
}

void Robot::remove()
{
	m_used = false;
}

bool Robot::isUsed()
{
	return m_used;
}


