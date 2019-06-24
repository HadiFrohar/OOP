#pragma once
#include "Object.h"
class ImmovableObject : public Object
{
public:
	ImmovableObject(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect);
	virtual ~ImmovableObject() = 0 {};
	virtual void collide(Object* object) = 0;
};

