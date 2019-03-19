#include "Rectangle.h"
#include "Utilities.h"



Rectangle::Rectangle()
{
	defaultRectangle();
}


void Rectangle::defaultRectangle()
{
	m_bottomLeft = setPoint(20, 10);
	m_topRight = setPoint(30, 20);
}

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
{
	if (isVaildIn(bottomLeft, topRight))
	{
		m_bottomLeft = bottomLeft;
		m_topRight = topRight;
	}
	else
		defaultRectangle();

}

Rectangle::Rectangle(const Vertex vertices[2])
{
	if (isVaildIn(vertices[0], vertices[1]))

	{
		m_bottomLeft = vertices[0];
		m_topRight = vertices[1];
	}
	else
		defaultRectangle();


}

Rectangle::Rectangle(double x0, double y0, double x1, double y1)
{
	m_bottomLeft = setPoint(x0, y0);
	m_topRight = setPoint(x1, y1);
	if (!isVaildIn(m_bottomLeft, m_topRight))
		defaultRectangle();
}

Rectangle::Rectangle(const Vertex& start, double width, double height)
{
	m_bottomLeft = start;
	m_topRight = setPoint(start.m_x + width, start.m_y + height);
	if (!isVaildIn(m_bottomLeft, m_topRight))
		defaultRectangle();

}

Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}


Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

double Rectangle::getHeight() const
{
	return m_topRight.m_y - m_bottomLeft.m_y;
}

double Rectangle::getWidth() const
{
	return m_topRight.m_x - m_bottomLeft.m_x;
}

bool Rectangle::isVaildIn(const Vertex& bottomLeft, const Vertex& topRight)
{
	if (bottomLeft.isValid() && topRight.isValid() &&
		topRight.isRighterThan(bottomLeft) && topRight.isHigherThan(bottomLeft))
		return true;
	return false;
}

bool Rectangle::isVaild() const
{
	if (m_bottomLeft.isValid() && m_topRight.isValid() &&
		m_topRight.isRighterThan(m_bottomLeft) && m_topRight.isHigherThan(m_bottomLeft))
		return true;
	return false;
}

void Rectangle::draw(Board& board) const
{
	Vertex m_topLeft,
		m_bottomRight;

	m_topLeft.m_x = m_bottomLeft.m_x;
	m_topLeft.m_y = m_topRight.m_y;
	m_bottomRight.m_x = m_topRight.m_x;
	m_bottomRight.m_y = m_bottomLeft.m_y;

	board.drawLine(m_bottomLeft, m_bottomRight);
	board.drawLine(m_bottomRight, m_topRight);
	board.drawLine(m_topRight, m_topLeft);
	board.drawLine(m_topLeft, m_bottomLeft);
}

Rectangle Rectangle::getBoundingRectangle() const
{
	Rectangle rectangle = Rectangle(m_bottomLeft, m_topRight);
	return rectangle;
}

double Rectangle::getArea() const
{
	return (m_topRight.m_y - m_bottomLeft.m_y) * (m_topRight.m_x - m_bottomLeft.m_x);
}

double Rectangle::getPerimeter() const
{
	return (m_topRight.m_y - m_bottomLeft.m_y) + (m_topRight.m_x - m_bottomLeft.m_x);
}

Vertex Rectangle::getCenter() const
{
	Vertex centerVertex;

	centerVertex.m_x = m_bottomLeft.m_x + (m_topRight.m_x - m_bottomLeft.m_x) / 2;
	centerVertex.m_y = m_bottomLeft.m_y + (m_topRight.m_y - m_bottomLeft.m_y) / 2;

	return centerVertex;
}

bool Rectangle::scale(double factor)
{
	m_bottomLeft.m_x += factor;
	m_bottomLeft.m_y += factor;
	m_topRight.m_x += factor;
	m_topRight.m_y += factor;

	if (isVaildIn(m_bottomLeft, m_topRight))
		return true;
	else
	{
		m_bottomLeft.m_x -= factor;
		m_bottomLeft.m_y -= factor;
		m_topRight.m_x -= factor;
		m_topRight.m_y -= factor;
		return false;
	}
}
