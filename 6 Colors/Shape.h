#pragma once
#include <SFML/Graphics.hpp>

class Shape : public sf::VertexArray
{
public:
	//derives from SFML vertex array shape, it gets type of shape and number of vertices
	explicit Shape(sf::PrimitiveType type, std::size_t vertexCount = 0);
	void updateColor(const sf::Color &color); //updates color of shape
	const sf::Color &getUsedColor() const; //returns the used color in shape
};

