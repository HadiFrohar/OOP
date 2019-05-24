#include "Rectangle.h"
#include "Settings.h"




Rectangle::Rectangle(const sf::Vector2f & pos, const sf::Color &color)
	:Shape(sf::Quads, 4)
{
	(*this)[1].position = pos;
	(*this)[2].position = { pos.x + SHAPE_SIZE, pos.y };
	(*this)[0].position = { pos.x, pos.y + SHAPE_SIZE };
	(*this)[3].position = { pos.x + SHAPE_SIZE, pos.y + SHAPE_SIZE };
	updateColor(color);
}

/*bool Rectangle::checkNearby(const std::shared_ptr<Shape>& shape)
{

	//CHECK_UP = (topLeft, downLeft)
	if (getTopLeft(*this) == getDownLeft(*shape))
		return true;
	//CHECK_DOWN = (downRight, topRight)
	else if (getDownRight(*this) == getTopRight(*shape))
		return true;
	//CHECK_RIGHT = (downRight, downLeft)
	else if (getDownRight(*this) == getDownLeft(*shape))
		return true;
	//CHECK_LEFT = (topLeft, topRight)
	else if (getTopLeft(*this) == getTopRight(*shape))
		return true;
	else
		return false;
}*/

