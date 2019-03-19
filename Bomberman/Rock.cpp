#include "Rock.h"



Rock::Rock(Position pos)
	:m_position(pos) //, m_onScreen(true)
{

}

Position Rock::getPosition()
{
	return m_position;
}

/*bool Rock::isBombed()
{
	return !m_onScreen;
}

void Rock::destroy()
{
	m_onScreen = false;
}*/

bool Rock::inBombRadius(std::vector<Bomb> bombs)
{
	for (size_t i = 0; i < bombs.size(); i++)
		if (bombs[i].isInRadius(m_position) && bombs[i].getTime() == 0)
			return true;
	return false;
}