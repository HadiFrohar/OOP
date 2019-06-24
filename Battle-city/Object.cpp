#include "Object.h"

Object::Object(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect)
{
	m_sprite.setPosition(pos);
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(*intRect);
}

void Object::draw(sf::RenderWindow * window)
{
	window->draw(m_sprite);
}

bool Object::collision(const Object * object1, const Object * object2)
{
	if (object1->getGlobalBounds().intersects(object2->getGlobalBounds()))
		return true;
	else
		return false;
}


void Object::updateSheetsController(SheetsController * controller)
{
	sheetsController = controller;
}

const sf::FloatRect Object::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

const sf::Vector2f Object::getPosition() const
{
	return m_sprite.getPosition();
}



bool Object::isOutsideGameBoard(const Object * object, sf::RectangleShape* gameBoard)
{
	if (object->m_sprite.getPosition().x > (gameBoard->getPosition().x + gameBoard->getGlobalBounds().width - object->getGlobalBounds().width) ||
		object->m_sprite.getPosition().x < gameBoard->getPosition().x || object->m_sprite.getPosition().y < gameBoard->getPosition().y ||
		object->m_sprite.getPosition().y >(gameBoard->getPosition().y + gameBoard->getGlobalBounds().width - object->getGlobalBounds().height))
		return true;
	return false;
}

SheetsController* Object::sheetsController = nullptr;

