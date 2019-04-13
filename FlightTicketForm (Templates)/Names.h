#pragma once
#include <vector>
#include <string>
#include <iostream>
class Names
{
public:

	//in this class we save names (like destination names, classes..)

	//adds name (to the vector)
	void addName(std::string);

	//returns specfic name (if it is not saved it will return the id that was passed)
	std::string getName(int) const;
private:
	std::vector<std::string> m_names; //names
};

