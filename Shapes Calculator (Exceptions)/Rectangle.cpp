#include "Rectangle.h"
#include "Utils.h"

#include <iostream>

using std::cout;
using std::endl;

Rectangle::Rectangle(std::istream& is)
: Shape("Rectangle")
{
	try {
		cout << "Please enter length of the width:" << endl;
		m_width = Utils::readInt(is);
		cout << "Please enter length of the height:" << endl;
		m_height = Utils::readInt(is);

	}
	catch(...)
	{
		throw;
	}
}

double Rectangle::area() const 
{
	return m_width * m_height;
}

double Rectangle::perimeter() const
{
	return m_height * 2 + m_width * 2;
}

void Rectangle::draw() const
{
	printDetails();
	cout << endl;

	for (int i = 1; i <= m_height; i++)
	{
		for (int j = 1; j <= m_width; j++)
		{
			if (i == 1 || i == m_height || j == 1 || j == m_width)
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

void Rectangle::printDetails() const
{
	printName();
	cout << "(w:" << m_width << ", h:" << m_height <<")";
}
