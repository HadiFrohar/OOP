#pragma once
#include "ImmovableObject.h"
class Water : public ImmovableObject
{
public:
	Water(const sf::Vector2f &pos);
	void draw(sf::RenderWindow *window) override; //draws, animates water
	void collide(Object* object) override;

private:
	sf::Clock m_aniClock; //clock for water animation
	pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>> m_intRectPair; //texture rect vector (for animation)
};

