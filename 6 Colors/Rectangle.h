#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
public:
	Rectangle(const sf::Vector2f& pos = sf::Vector2f(0, 0), const sf::Color &color=sf::Color::Black);
	//bool checkNearby(const std::shared_ptr<Shape>& shape) override;

};

