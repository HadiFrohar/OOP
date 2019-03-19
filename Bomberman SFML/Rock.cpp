#include "Rock.h"

Rock::Rock(const sf::Vector2f & pos, const sf::Texture& sheets)
	:UnmoveableObject(pos, sheets)

{
	//GUARD_X =300, GUARD_Y=100
	setType(ROCK, sf::IntRect(FOURTH, FIFTH, OBJECTIMGSIZE, OBJECTIMGSIZE));
}
