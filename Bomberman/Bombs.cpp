#include "Bomb.h"



Bomb::Bomb(Position pos)
	:m_position(pos)
{
	m_time = 5;
}

/*void Bomb::setPosition(short row, short col)
{
	m_position.row = row;
	m_position.col = col;
}*/

Position Bomb::getPosition()
{
	return m_position;
}

bool Bomb::isInRadius(Position pos)
{
	if ((pos.row == m_position.row && pos.col == m_position.col) ||
		(pos.row == m_position.row && pos.col == m_position.col - 1) ||
		(pos.row == m_position.row && pos.col == m_position.col + 1) ||
		(pos.row == m_position.row - 1 && pos.col == m_position.col) ||
		(pos.row == m_position.row + 1 && pos.col == m_position.col))
		return true;
	return false;
}

/*void Bomb::setTime()
{
	m_time = 5;
}*/

void Bomb::decreaseTime()
{
	m_time--;
}

short Bomb::getTime()
{
	return m_time;
}