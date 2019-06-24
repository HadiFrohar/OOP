#pragma once
#include "Object.h"
class MovableObject : public Object
{
public:
	MovableObject(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect);
	virtual ~MovableObject() = 0 {};
	virtual void collide(Object* object) = 0;
};

