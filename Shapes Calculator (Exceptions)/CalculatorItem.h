#pragma once
class CalculatorItem
{
public:
	CalculatorItem() = default;
	virtual ~CalculatorItem() = default;
	virtual double area() const = 0; //calculates item area and prints it
	virtual double perimeter() const = 0; //calculates item perimeter and prints it
	virtual void draw() const = 0; //draws item
	virtual void printDetails() const = 0; //prints item type and details (such as width, height)
};

