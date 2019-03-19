#include "Box.h"
#include "Utilities.h"


Box::Box()
{
}

Box::Box(const sf::Vector2f & pos, const sf::Texture& sheets)
	: m_position(pos), m_texture(sheets)
{

}

void Box::draw(sf::RenderWindow& window)
{

	createShape();
	createText();
	window.draw(m_shape);
	window.draw(m_text);
}

void Box::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
}


sf::Vector2f Box::getPosition()
{
	return m_position;
}

void Box::setHeight(float height)
{
	m_height = height;
}

void Box::setWidth(float width)
{
	m_width = width;
}

void Box::setFont(sf::Font & font)
{
	m_font = font;
}

void Box::updateText(std::string text)
{
	m_string = text;
}

void Box::setSheets(const sf::Texture & sheets)
{
	m_texture = sheets;
}

void Box::setImgPosition(const sf::IntRect & imgPos)
{
	m_imgPos = imgPos;
}



void Box::createShape()
{
	m_shape.setTexture(m_texture);
	m_shape.setTextureRect(m_imgPos);
	m_shape.setPosition(m_position);
}

void Box::createText()
{
	m_text.setFont(m_font);
	m_text.setString(m_string);
	m_text.setCharacterSize(FONTSIZE);
	m_text.setFillColor(sf::Color::White);
	m_text.setStyle(sf::Text::Bold);
	m_text.setPosition({m_position.x, m_position.y + OBJECTSIZE - FONTSIZE });
	m_text.setOrigin(-m_shape.getGlobalBounds().width / 2 + m_text.getGlobalBounds().width / 2, 0);
}
