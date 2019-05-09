#include "Subtraction.h"
#include <iostream>
using std::cout;
using std::endl;

Subtraction::Subtraction(std::istream& is, const Calculator& calculator)
	: BinaryOperation(is, calculator) { }

double Subtraction::area() const
{
	return m_item1->area() - m_item2->area();
}

double Subtraction::perimeter() const
{
	return m_item1->perimeter() - m_item2->perimeter();
}

void Subtraction::draw() const
{
	m_item1->draw();
	cout << "\t-" << endl;
	m_item2->draw();
}

void Subtraction::printDetails() const
{
	cout << "(";
	m_item1->printDetails();
	cout << ") - (";
	m_item2->printDetails();
	cout << ")";
}
