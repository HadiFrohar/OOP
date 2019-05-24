#include "ColorRectangle.h"
#include "Settings.h"



ColorRectangle::ColorRectangle(const sf::Color & usedColor, const sf::Vector2f & pos, const float size)
	:m_usedColor(usedColor)
{
	m_rectangle.setSize({ size, size });
	m_rectangle.setOutlineColor(BLACK);
	m_rectangle.setOutlineThickness(1);
	m_rectangle.setFillColor(usedColor);
	m_rectangle.setPosition(pos);
}

void ColorRectangle::enable()
{
	m_rectangle.setFillColor(m_usedColor);
}

void ColorRectangle::disable()
{
	m_rectangle.setFillColor(BLACK);
}

bool ColorRectangle::enabled()
{
	return (m_rectangle.getFillColor() == m_usedColor);
}

sf::RectangleShape & ColorRectangle::getShape()
{
	return m_rectangle;
}
