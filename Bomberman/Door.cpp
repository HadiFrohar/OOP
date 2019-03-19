#include "Door.h"



Door::Door()
//	: m_hidden(false)
{
}

void Door::setPosition(short row, short col)
{
	m_position.row = row;
	m_position.col = col;
}
Position Door::getPosition()
{
	return m_position;
}

/*bool Door::isHidden()
{
	return m_hidden;
}*/