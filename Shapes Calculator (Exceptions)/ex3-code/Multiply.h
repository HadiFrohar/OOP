//A class that holds an object from the list and multiplies it by a given number
#pragma once
#include <memory>
#include "CalculatorItem.h"

class Calculator;

class Multiply : public CalculatorItem
{
public:
	Multiply(std::istream& is, const Calculator& calculator);
	virtual ~Multiply() = default;
	double area() const override;
	double perimeter() const override;
	void printDetails() const override;
	void draw() const override;
private:
	unsigned int m_multi;
	std::shared_ptr<CalculatorItem> m_item;
};

