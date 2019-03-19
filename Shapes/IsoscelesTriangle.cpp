#include "IsoscelesTriangle.h"
#include "Utilities.h"

IsoscelesTriangle::IsoscelesTriangle() {
	defaultTriangle();
}

void IsoscelesTriangle::defaultTriangle() {
	m_vertices[0] = setPoint(20, 20);
	m_vertices[1] = setPoint(25, 25);
	m_vertices[2] = setPoint(30, 20);
}

IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
{
	if (isVaildIn(vertices))
	{
		m_vertices[0] = vertices[0];
		m_vertices[1] = vertices[1];
		m_vertices[2] = vertices[2];

	}
	else
		defaultTriangle();
}

IsoscelesTriangle::IsoscelesTriangle(const Vertex& center, double width, double height)
{

	m_vertices[0] = setPoint(center.m_x - width / 2, center.m_y - height / 2);
	m_vertices[1] = setPoint(center.m_x, center.m_y + height / 2);
	m_vertices[2] = setPoint(center.m_x + width / 2, center.m_y - height / 2);
	
	if (!isVaildIn(m_vertices))
		defaultTriangle();
}

Vertex IsoscelesTriangle::getVertex(int index) const
{
	return m_vertices[index];
}

double IsoscelesTriangle::getLength() const
{
	return m_vertices[2].m_x - m_vertices[0].m_x;
}


double IsoscelesTriangle::getScelesLength() const
{
	return distance(m_vertices[0], m_vertices[1]);
}

double IsoscelesTriangle::getHeight() const
{
	return m_vertices[1].m_y - m_vertices[0].m_y;
}

bool IsoscelesTriangle::isVaildIn(const Vertex vertices[3])
{
	if (vertices[0].isValid() && vertices[1].isValid() && vertices[2].isValid() &&
		sameY(vertices[0], vertices[2]))
		return true;

	return false;
}

bool IsoscelesTriangle::isVaild() const
{
	if (m_vertices[0].isValid() && m_vertices[1].isValid() && m_vertices[2].isValid() &&
		sameY(m_vertices[0], m_vertices[2]))
		return true;

	return false;
}

void IsoscelesTriangle::draw(Board& board) const
{
	board.drawLine(m_vertices[0], m_vertices[2]);
	board.drawLine(m_vertices[0], m_vertices[1]);
	board.drawLine(m_vertices[2], m_vertices[1]);
}

Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	Rectangle rectangle;
	Vertex bottomLeft,
		topRight;

	bottomLeft = m_vertices[0];
	topRight.m_y = m_vertices[1].m_y;
	topRight.m_x = m_vertices[2].m_x;

	rectangle = Rectangle(bottomLeft, topRight);

	return rectangle;
}

double IsoscelesTriangle::getArea() const
{
	return (getHeight()*getLength()) / 2;
}

double IsoscelesTriangle::getPerimeter() const
{
	return (distance(m_vertices[0], m_vertices[1]) + distance(m_vertices[0], m_vertices[2]) + distance(m_vertices[1], m_vertices[2]));
}

Vertex IsoscelesTriangle::getCenter() const
{
	Vertex centerVertex;
	centerVertex.m_x = m_vertices[0].m_x;
	centerVertex.m_y = m_vertices[1].m_y;
	
	return centerVertex;
}

bool IsoscelesTriangle::scale(double factor)
{
	m_vertices[0].m_x += factor;
	m_vertices[0].m_y += factor;
	m_vertices[1].m_x += factor;
	m_vertices[1].m_y += factor;
	m_vertices[2].m_x += factor;
	m_vertices[2].m_y += factor;

	if (isVaildIn(m_vertices))
		return true;
	else
	{
		m_vertices[0].m_x -= factor;
		m_vertices[0].m_y -= factor;
		m_vertices[1].m_x -= factor;
		m_vertices[1].m_y -= factor;
		m_vertices[2].m_x -= factor;
		m_vertices[2].m_y -= factor;

		return false;
	}
}