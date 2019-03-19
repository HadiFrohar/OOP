#include "Button.h"
#include "Utilities.h"


Button::Button(const sf::Vector2f& pos, std::string image)
	: m_position(pos)
{
	m_texture.loadFromFile(image);
}

void Button::draw(sf::RenderWindow& window)
{

	window.draw(createShape());
}

bool Button::click(const sf::Vector2f& pos)
{
	sf::RectangleShape rect = createShape();
	if (rect.getGlobalBounds().contains(pos))
	{
		if (clicked)
			clicked = false;
		else
			clicked = true;

		return true;
	}
	return false;
}

void Button::unclick()
{
	clicked = false;
}

sf::RectangleShape Button::createShape() const
{
	sf::RectangleShape rect({ BUTTON_SIZE, BUTTON_SIZE });


	rect.setPosition(m_position);
	rect.setTexture(&m_texture);
	rect.setOutlineThickness(3);


	if (clicked)
		rect.setOutlineColor(sf::Color::Red);
	else
		rect.setOutlineColor(sf::Color::Black);


	return rect;
}