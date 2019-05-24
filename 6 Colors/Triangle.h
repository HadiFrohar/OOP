#pragma once
#include "Shape.h"
class Triangle : public Shape
{
public:
	//creates triangle
	Triangle(const sf::Vector2f& pos = sf::Vector2f(0, 0), const sf::Color &color = sf::Color::Black, bool up=true);
	//bool checkNearby(const std::shared_ptr<Shape>& shape) override;

private:
	bool m_up;
};

