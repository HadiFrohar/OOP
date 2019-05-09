#include "Add.h"
#include <iostream>
using std::cout;
using std::endl;

Add::Add(std::istream& is, const Calculator& calculator)
	: BinaryOperation(is, calculator) { }

//Add::Add(std::shared_ptr<CalculatorItem> item1, std::shared_ptr<CalculatorItem> item2)
//: BinaryOperation(item1, item2)
//{}

double Add::area() const
{
	return m_item1->area() + m_item2->area();
}

double Add::perimeter() const
{
	return m_item1->perimeter() + m_item2->perimeter();
}

void Add::draw() const
{
	m_item1->draw();
	cout << "\t+" << endl;
	m_item2->draw();
}

void Add::printDetails() const
{
	cout << "(";
	m_item1->printDetails();
	cout << ") + (";
	m_item2->printDetails();
	cout << ")";
}