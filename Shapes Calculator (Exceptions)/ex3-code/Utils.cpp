#include "Utils.h"
#include "Exceptions.h"
#include <iostream>


int Utils::readInt(std::istream& is)
{
	int number;
	is.exceptions(std::ios_base::badbit | std::ios_base::failbit); 
	try //try to read integer
	{
		is >> number;
	}
	catch (std::istream::failure &)
	{
		cleanStream(is);
		std::cout << "Type must be integer, ";
		throw;
	}
	if (number < 0)
		throw OutOfRange();

	return number;
}

char Utils::readChar(std::istream & is)
{
	char c;
	is >> c;
	cleanStream(is);
	return c;
}

void Utils::cleanStream(std::istream & is)
{
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
