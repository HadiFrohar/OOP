#include "Object.h"



Object::Object()
	:m_size(1.0f)
{
}

Object::Object(const sf::Vector2f & pos, const sf::Texture& sheets)
	:m_position(pos), m_sheets(sheets), m_size(1.0f)
{
}

void Object::draw(sf::RenderWindow & window)
{

	createShape();
	window.draw(m_shape);
}

void Object::setPoisiton(const sf::Vector2f & pos)
{
	m_position = pos;
}

sf::Vector2f Object::getPosition()
{
	return m_position;
}

sf::Vector2f & Object::getPositionAsRef()
{
	return m_position;
}

void Object::setType(char type, sf::IntRect imgPos)
{
	m_type = type;
	m_imgPos = imgPos;
}

void Object::setSheets(sf::Texture & sheets)
{
	m_sheets = sheets;
}

sf::Texture & Object::getSheets()
{
	return m_sheets;
}

char &Object::getType()
{
	return m_type;
}

void Object::setImgPos(sf::IntRect imgPos)
{
	m_imgPos = imgPos;
}

bool Object::collision(sf::Sprite sprite)
{


	createShape();
	if (m_shape.getGlobalBounds().intersects(sprite.getGlobalBounds()))
		return true;

	return false;
}

void Object::setSize(float size)
{
	m_size = size;
}

sf::Sprite & Object::getShape()
{

	m_size -= (float)0.05;
	createShape();
	m_size += (float)0.05;
	return m_shape;

}
void Object::createShape()
{
	m_shape.setTexture(m_sheets);
	m_shape.setTextureRect(m_imgPos);
	m_shape.setPosition(m_position);
	m_shape.setScale(m_size, m_size);
}

