#include "Wall.h"

Wall::Wall(const sf::Vector2f & pos, const sf::Texture & texture, shared_ptr<sf::IntRect>& intRect)\
	:ImmovableObject(pos, texture, intRect)
{
}

void Wall::collide(Object * object)
{
	if(collision(this, object))
		object->collideWith(this);
}
