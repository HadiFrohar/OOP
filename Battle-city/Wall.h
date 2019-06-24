#pragma once
#include "ImmovableObject.h"
class Wall : public ImmovableObject
{
public:
	Wall(const sf::Vector2f &pos, const sf::Texture &texture, shared_ptr<sf::IntRect> &intRect);
	virtual ~Wall() = 0 {};
	void collide(Object* object) override; //calls object.collideWith(this)
};

