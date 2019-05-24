#include "Triangle.h"
#include "Settings.h"



Triangle::Triangle(const sf::Vector2f & pos, const sf::Color & color, bool up)
	:Shape(sf::Triangles, 3), m_up(up)
{
	(*this)[0].position = pos;

	if (up)
		(*this)[1].position = { pos.x + SHAPE_SIZE, pos.y };
	else
		(*this)[1].position = { pos.x, pos.y + SHAPE_SIZE };

	(*this)[2].position = { pos.x + SHAPE_SIZE, pos.y + SHAPE_SIZE };
	updateColor(color);
}

/*bool Triangle::checkNearby(const std::shared_ptr<Shape>& shape)
{
	if (m_up)
	{
		//CHECK_UP = (topRight, downRight)
		if (getTopRight(*this) == getDownRight(*shape))
			return true;
		//CHECK_DOWN, CHECK_LEFT = (topLeft, topLeft)
		else if (getTopLeft(*this) == getTopLeft(*shape))
			return true;
		//CHECK_RIGHT = (topRight, topLeft)
		else if (getTopRight(*this) == getTopLeft(*shape))
			return true;
		else
			return false;
	}
	else
	{
		//CHECK_UP, CHECK_RIGHT = (topLeft, topLeft)
		if (getTopLeft(*this) == getTopLeft(*shape))
			return true;
		//CHECK_DOWN = (downLeft, topLeft)
		else if (getDownLeft(*this) == getTopLeft(*shape))
			return true;
		//CHECK_LEFT = (downLeft, downRight)
		else if (getDownLeft(*this) == getDownRight(*shape))
			return true;
		else
			return false;
	}
}*/