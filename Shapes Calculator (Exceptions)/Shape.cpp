#include "Shape.h"
#include <iostream>

Shape::Shape(const std::string& name) 
: m_name(name) 
{ }


void Shape::printName() const
{
	std::cout << m_name;
}




