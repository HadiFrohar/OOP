#include "House.h"


House::House() 
{
	defaultHouse();
	
}

void House::defaultHouse()
{
	Vertex bottomLeft,
		topRight,
		vertices[3];

	bottomLeft = setPoint(20, 10);
	topRight = setPoint(30, 20);
	vertices[0] = setPoint(20, 20);
	vertices[1] = setPoint(25, 25);
	vertices[2] = setPoint(30, 20);


	Rectangle rectangle = Rectangle::Rectangle(bottomLeft, topRight);
	IsoscelesTriangle triangle = IsoscelesTriangle::IsoscelesTriangle(vertices);
}

House::House(const Rectangle& rectangle, const IsoscelesTriangle& triangle)
{

	if (isVaild(rectangle, triangle))
	{
		m_rectangle = rectangle;
		m_triangle = triangle;
	}
	else
		defaultHouse();
}

House::House(const Vertex& roofTop, double width, double roofHeight, double baseHeight)
{
	Vertex vertices[3],
		bottomLeft;

	Rectangle rectangle;
	IsoscelesTriangle triangle;

	vertices[0] = setPoint(roofTop.m_x - width / 2, roofTop.m_y - roofHeight);
	vertices[1] = setPoint(roofTop.m_x + width / 2, roofTop.m_y - roofHeight);
	vertices[3] = roofTop;
	bottomLeft = setPoint(vertices[0].m_x, vertices[0].m_y - baseHeight);

	if (!vertices[0].isValid() || !vertices[1].isValid() || !vertices[3].isValid() || !bottomLeft.isValid())
		defaultHouse();
	else
	{
		triangle = IsoscelesTriangle::IsoscelesTriangle(vertices);
		rectangle = Rectangle(bottomLeft, vertices[1]);
	}

}

bool House::extendRoof(double width)
{
	double first,
		second;

	Vertex vertices[3];

	if (width > 0 && width > m_triangle.getLength())
	{
		first = m_triangle.getVertex(0).m_x - width / 2;
		if (first<0 || first>MAX_X)
			return false;

		second = m_triangle.getVertex(2).m_x + width / 2;
		if (first<0 || first>MAX_X)
			return false;
	
		vertices[0] = m_triangle.getVertex(0);
		vertices[1] = m_triangle.getVertex(1);
		vertices[2] = m_triangle.getVertex(2);

		vertices[0].m_x = first;
		vertices[2].m_x = second;

		m_triangle = IsoscelesTriangle::IsoscelesTriangle(vertices);
		return true;
	}

	return false;

}

double House::getHeight() const
{
	return m_triangle.getVertex(2).m_y - m_rectangle.getBottomLeft().m_y;
}

double House::getWidthDifference() const
{
	return m_triangle.getLength() - m_rectangle.getWidth();
}

bool House::isVaild(Rectangle rectangle, IsoscelesTriangle triangle) {
	if (sameY(rectangle.getTopRight(), triangle.getVertex(0)) &&
		triangle.getLength() >= rectangle.getWidth() && rectangle.isVaild())
		return true;
	return false;
}


void House::draw(Board& board) const
{
	m_rectangle.draw(board);
	m_triangle.draw(board);
}


Rectangle House::getBoundingRectangle() const
{
	Rectangle rectangle;
	Vertex bottomLeft,
		topRight;

	bottomLeft = m_rectangle.getBottomLeft();
	topRight.m_y = m_triangle.getVertex(1).m_y;
	topRight.m_x = m_triangle.getVertex(2).m_x;

	rectangle = Rectangle(bottomLeft, topRight);

	return rectangle;
}

double House::getArea() const
{
	return m_triangle.getArea() + m_rectangle.getArea();
}

double House::getPerimeter() const
{
	return (m_rectangle.getPerimeter() - m_rectangle.getWidth()) + (m_triangle.getPerimeter() - m_triangle.getLength());
}

Vertex House::getCenter() const
{
	Vertex centerVertex;

	centerVertex.m_y = m_triangle.getVertex(0).m_y;
	centerVertex.m_x = m_triangle.getVertex(1).m_x;

	return centerVertex;
}

bool House::scale(double factor)
{
	if (m_rectangle.scale(factor))
		if (m_triangle.scale(factor))
			return true;
		else
			m_rectangle.scale(-factor);

	return false;
}