#include "Door.h"

Door::Door()
	:UnmoveableObject()

{
	//GUARD_X =0, GUARD_Y=100
	setType(DOOR, sf::IntRect(FOURTH, SEVENTH, OBJECTIMGSIZE, OBJECTIMGSIZE));
}

void Door::clear()
{
	setPoisiton({ 0,0 });
}
