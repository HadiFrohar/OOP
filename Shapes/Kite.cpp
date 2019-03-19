#include "Kite.h"



Kite::Kite()
{
	defaultKite();

}

void Kite::defaultKite()
{
	Vertex vertices[3];
	vertices[0] = setPoint(20, 20);
	vertices[1] = setPoint(25, 25);
	vertices[2] = setPoint(30, 20);
	m_triangles[0] = IsoscelesTriangle::IsoscelesTriangle(vertices);

	vertices[0] = setPoint(20, 20);
	vertices[1] = setPoint(25, 15);
	vertices[2] = setPoint(30, 20);
	m_triangles[1] = IsoscelesTriangle::IsoscelesTriangle(vertices);
}

Kite::Kite(const IsoscelesTriangle triangles[2])
{
	if (isVaildIn(triangles))
	{
		m_triangles[0] = triangles[0];
		m_triangles[1] = triangles[1];
	}
	else
		defaultKite();
}

Kite::Kite(const Vertex& top, double width, double topHeight, double bottomHeight)
{
	IsoscelesTriangle triangles[2];
	Vertex vertices[3];

	vertices[0].m_y = top.m_y - topHeight;
	vertices[0].m_x = top.m_x - width / 2;

	vertices[1] = top;

	vertices[2].m_y = vertices[0].m_y;
	vertices[2].m_x = top.m_x + width / 2;

	triangles[0] = IsoscelesTriangle::IsoscelesTriangle(vertices);

	vertices[0].m_y = top.m_y - topHeight;
	vertices[0].m_x = top.m_x - width / 2;

	vertices[1].m_y = top.m_y - topHeight - bottomHeight;

	vertices[2].m_y = vertices[0].m_y;
	vertices[2].m_x = top.m_x + width / 2;

	triangles[1] = IsoscelesTriangle::IsoscelesTriangle(vertices);

	if (isVaildIn(triangles))
	{
		m_triangles[0] = triangles[0];
		m_triangles[1] = triangles[1];
	}
	else
		defaultKite();

}

double Kite::getTotalHeight() const
{
	return distance(m_triangles[0].getVertex(1), m_triangles[1].getVertex(1));
}

bool Kite::isVaildIn(const IsoscelesTriangle triangles[2])
{
	if (triangles[0].isVaild() && triangles[1].isVaild() &&
		triangles[0].getVertex(0).isEqual(triangles[1].getVertex(0)) &&
		triangles[0].getVertex(2).isEqual(triangles[1].getVertex(2 )) &&
		sameX(triangles[0].getVertex(1), triangles[1].getVertex(1)) &&
		triangles[0].getVertex(1).isHigherThan(triangles[1].getVertex(1)))
		return true;
	else
		return false;
}

void Kite::draw(Board& board) const
{
	m_triangles[0].draw(board);
	m_triangles[1].draw(board);
}

Rectangle Kite::getBoundingRectangle() const
{
	Rectangle rectangle;
	Vertex bottomLeft,
		topRight;

	bottomLeft.m_y = m_triangles[1].getVertex(1).m_y;
	bottomLeft.m_x = m_triangles[1].getVertex(0).m_x;
	topRight.m_y = m_triangles[0].getVertex(1).m_y;
	topRight.m_x = m_triangles[0].getVertex(2).m_x;

	rectangle = Rectangle(bottomLeft, topRight);

	return rectangle;
}

double Kite::getArea() const
{
	return m_triangles[0].getArea() + m_triangles[1].getArea();
}

double Kite::getPerimeter() const
{
	return (m_triangles[0].getPerimeter() + m_triangles[1].getPerimeter() - 2*m_triangles[1].getLength());
}

Vertex Kite::getCenter() const
{
	Vertex centerVertex;
	centerVertex.m_x = m_triangles[0].getVertex(1).m_x;
	centerVertex.m_y = m_triangles[0].getVertex(1).m_y - distance(m_triangles[0].getVertex(1), m_triangles[1].getVertex(1));

	return centerVertex;
}


bool Kite::scale(double factor)
{
	if (m_triangles[0].scale(factor))
		if (m_triangles[1].scale(factor))
			return true;
		else
			m_triangles[0].scale(-factor);
	
	return false;
}