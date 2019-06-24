#include "ImmovableObject.h"



ImmovableObject::ImmovableObject(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect)
	:Object(pos, texture, intRect)
{
}
