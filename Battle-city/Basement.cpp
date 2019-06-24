#include "Basement.h"



Basement::Basement(const sf::Vector2f & pos, const sf::Texture & texture, pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>> intRectPair)
	:ImmovableObject(pos, texture, intRectPair.first), m_intRectPair(intRectPair), m_destroyed(false)
{
}



void Basement::destroy()
{
	m_destroyed = true;
	m_sprite.setTextureRect(*m_intRectPair.second);
}

bool Basement::isDestroyed() const
{
	return m_destroyed;
}

void Basement::restart()
{
	m_sprite.setTextureRect(*m_intRectPair.first);
	m_destroyed = false;
}

void Basement::collide(Object * object)
{
	if(collision(this, object))
		object->collideWith(this);
}

void Basement::collideWith(Bullet * bullet)
{
	destroy();
}

