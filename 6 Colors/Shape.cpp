#include "Shape.h"




Shape::Shape(sf::PrimitiveType type, std::size_t vertexCount)
	:sf::VertexArray(type, vertexCount)
{
}


void Shape::updateColor(const sf::Color & color)
{
	for (size_t i = 0; i < getVertexCount(); i++)
		(*this)[i].color = color;
}

const sf::Color & Shape::getUsedColor() const
{
	return (*this)[0].color;
}

/*sf::Vector2f Shape::getTopLeft(const sf::VertexArray & shape)
{
	return sf::Vector2f(shape.getBounds().left, shape.getBounds().top);
}

sf::Vector2f Shape::getTopRight(const sf::VertexArray & shape)
{
	return sf::Vector2f(shape.getBounds().left + shape.getBounds().width, shape.getBounds().top);
}

sf::Vector2f Shape::getDownLeft(const sf::VertexArray & shape)
{
	return sf::Vector2f(shape.getBounds().left, shape.getBounds().top + shape.getBounds().height);
}

sf::Vector2f Shape::getDownRight(const sf::VertexArray & shape)
{
	return sf::Vector2f(shape.getBounds().left + shape.getBounds().width, shape.getBounds().top + shape.getBounds().height);
}*/
