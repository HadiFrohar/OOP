#pragma once
#include "Shape.h"
const double PI = 3.141592653589793238463;

class Circle : public Shape
{
protected:
	double m_radius;
public:
	Circle(std::istream& is);
	virtual ~Circle() = default;
	double area() const override;
	double perimeter() const override;
	void draw() const override;
	void printDetails()const override;
};

