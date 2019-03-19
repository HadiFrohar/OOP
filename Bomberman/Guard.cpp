#include "Guard.h"
#include "screen.h"

Guard::Guard()
{

}

void Guard::setPosition(short row, short col)
{
	m_position.row = row;
	m_position.col = col;
}

Position Guard::getPosition()
{
	return m_position;
}


void Guard::moveUp()
{
	m_position.row--;
}
void Guard::moveDown()
{
	m_position.row++;
}
void Guard::moveLeft()
{
	m_position.col--;
}
void Guard::moveRight()
{
	m_position.col++;
}

bool Guard::canMove(char c)
{
	if (c == WALL || c == ROCK || c==DOOR)
		return false;
	return true;
}

bool Guard::onBomb(std::vector<Bomb> bombs)
{
	for (size_t i = 0; i < bombs.size(); i++)
		if (bombs[i].isInRadius(m_position) && bombs[i].getTime() == 0)
			return true;
	return false;
}