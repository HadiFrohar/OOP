#include "Multiply.h"
#include <iostream>
#include "Utils.h"
#include "Calculator.h"

using std::cout;
using std::endl;

Multiply::Multiply(std::istream& is, const Calculator& calculator)
{
	m_item = calculator[Utils::readInt(is)];
	m_multi = Utils::readInt(is);
}

double Multiply::area() const
{
	return m_item->area() * m_multi;
}

double Multiply::perimeter() const
{
	return m_item->perimeter() * m_multi;
}

void Multiply::draw() const
{
	m_item->draw();
	cout << "\tx" << m_multi << endl;
}

void Multiply::printDetails() const
{
	cout << "(";
	m_item->printDetails();
	cout << ") * (" << m_multi << ") times";
}