#pragma once
#include "ImmovableObject.h"
class Basement : public ImmovableObject
{
public:
	Basement(const sf::Vector2f & pos, const sf::Texture & texture, pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>> intRectPair);
	bool isDestroyed() const; //returns if basement is destoryed or not, (by befault not)
	void restart(); //restarts basement (if basement destroyed then it will !)
	void collide(Object* object) override; //calls object.colideWith(this)
	void collideWith(Bullet* bullet) override; //basement collides with bullet reaction
private:
	void destroy(); //destroys basement
	bool m_destroyed; //states if basement destroyed or not
	pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>> m_intRectPair; //basement shape (destroyed or not)
};

