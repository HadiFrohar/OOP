#pragma once
#include "ImmovableObject.h"
class Bushes : public ImmovableObject
{
public:
	Bushes(const sf::Vector2f &pos); //pases bushes IntRect, texture to ImmovableObject
	void collide(Object* object) override; //calls object.collideWith(this)
};

