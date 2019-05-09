#include "Circle.h"
#include "Utils.h"

#include <iostream>
using std::cout;

Circle::Circle(std::istream& is)
: Shape("Circle")
{
	try
	{
		cout << "Please enter length of the radius:" << std::endl;
		m_radius = Utils::readInt(is);
	}
	catch (...)
	{
		throw;
	}
}

void Circle::printDetails() const
{
	printName();
	cout << "(r:" << m_radius << ")" ;
}

//calculate the area of circle
double Circle::area() const
{
	return m_radius * m_radius*PI;
}

//calculate the perimeter of circle
double Circle::perimeter() const 
{
	return 2 * m_radius * PI;
}

void Circle::draw() const
{
	printDetails();
	cout << std::endl;

	// for horizontal movement 
	for (int i = 0; i <= 2 * m_radius; i++) {

		// for vertical movement 
		for (int j = 0; j <= 2 * m_radius; j++) {
			const float dist = (float) sqrt((i - m_radius) * (i - m_radius) +
				(j - m_radius) * (j - m_radius));

			// dist should be in the range (radius - 0.5) 
			// and (radius + 0.5) to print stars(*) 
			if (dist > m_radius - 0.5 && dist < m_radius + 0.5)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}
