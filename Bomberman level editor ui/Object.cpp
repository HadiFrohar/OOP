#include "Object.h"
#include "Utilities.h"

Object::Object()
{
}

Object::Object(const sf::Vector2f& pos)
	: m_position(pos)
{
}

void Object::draw(sf::RenderWindow& window)
{
	window.draw(createShape());
}

bool Object::click(const sf::Vector2f& pos)
{
	sf::RectangleShape type = createShape();
	if (type.getGlobalBounds().contains(pos))
	{
		return true;
	}
	return false;
}

void Object::setPosition(const sf::Vector2f & pos)
{
	m_position = pos;
}

sf::Vector2f Object::getPosition()
{
	return m_position;
}

void Object::setType(char type, std::string imgPath)
{
	m_type = type;
	m_imgPath = imgPath;
	m_texture.loadFromFile(m_imgPath);
}

char Object::getType()
{
	return m_type;
}

void Object::mouseOver()
{
	m_mouseOver = true;
}

void Object::mouseNotOver()
{
	m_mouseOver = false;
}

bool Object::isMouseOver()
{
	return m_mouseOver;
}

sf::RectangleShape Object::createShape() const
{
	sf::RectangleShape type({ DEFAULT_SIZE, DEFAULT_SIZE });
	if (m_mouseOver)
	{
		type.setOutlineThickness(1);
		type.setOutlineColor(sf::Color::Red);
	}

	type.setPosition(m_position);
	type.setTexture(&m_texture);
	return type;
}


