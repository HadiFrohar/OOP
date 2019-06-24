#include "Water.h"






Water::Water(const sf::Vector2f & pos)
	:ImmovableObject(pos, sheetsController->treeWater->getSheets(), sheetsController->treeWater->getData()[1])
{
	m_intRectPair = std::make_pair(sheetsController->treeWater->getData()[1], sheetsController->treeWater->getData()[2]);
}


void Water::draw(sf::RenderWindow * window)
{
	if (m_aniClock.getElapsedTime().asSeconds() > 1)
	{
		if (m_sprite.getTextureRect() == *m_intRectPair.first)
			m_sprite.setTextureRect(*m_intRectPair.second);
		else
			m_sprite.setTextureRect(*m_intRectPair.first);
		m_aniClock.restart();

	}
	Object::draw(window);
}

void Water::collide(Object * object)
{
	if(collision(this, object))
		object->collideWith(this);
}

