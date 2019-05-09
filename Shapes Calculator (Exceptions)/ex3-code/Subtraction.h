//A class of subtraction between 2 objects from the list, 
//Calculating the circumference and area will be subtraction between the areas of the objects / 
//subtract between the circumference of the objects
#pragma once
#include <memory>
#include "BinaryOperation.h"

class Subtraction: public BinaryOperation
{
public:
	Subtraction(std::istream& is, const Calculator& calculator);
	virtual ~Subtraction() = default;
	double area() const override;
	double perimeter() const override;
	void draw() const override;
	void printDetails() const override;
};

