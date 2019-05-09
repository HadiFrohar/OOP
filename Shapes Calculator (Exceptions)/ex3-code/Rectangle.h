#pragma once
#include "Shape.h"

class Rectangle: public Shape
{
public:
	Rectangle(std::istream& is);
	virtual ~Rectangle() = default;
	double area() const override;
	double perimeter() const override;
	void printDetails() const override;
	void draw() const override;
private:
	int m_width{};
	int m_height{};
};

