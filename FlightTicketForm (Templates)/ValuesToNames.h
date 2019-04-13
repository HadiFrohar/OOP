#pragma once
#include "Names.h"
#include <iostream>
template<typename T = Names>
class ValuesToNames
{
public:
	//This class converts value to name (based on what is saved in class)
	ValuesToNames(int id = 0);

	//returns the approprite name of the value that is saved
	std::string valueToName() const;

	//input function, it reads an int (value)
	template <typename T>
	friend std::istream& operator>>(std::istream&os, ValuesToNames<T> & val);

	//returns the value that is saved in the object
	int getValue() const;

private:
	T m_names; //object that converts the id to name (type Names)
	int m_value; //saved value
};

template <typename T>
std::ostream & operator<<(std::ostream&os, const ValuesToNames<T> & val)
{
	os << val.valueToName();
	return os;
}

template <typename T>
std::istream& operator>>(std::istream&os, ValuesToNames<T> & val)
{
	os >> val.m_value;
	return os;
}



template<typename T>
ValuesToNames<T>::ValuesToNames(int id)
	:m_value(id)
{
}

template <typename T>
std::string ValuesToNames<T>::valueToName() const
{
	return m_names.getName(m_value);
}

template<typename T>
int ValuesToNames<T>::getValue() const

{
	return m_value;
}


template<typename T>
bool operator<=(const ValuesToNames<T> names, const ValuesToNames<T> other)
{
	return (names.getValue() <= other.getValue());
}

template<typename T>
bool operator>=(const ValuesToNames<T> names, const ValuesToNames<T> other)
{
	return (names.getValue() >= other.getValue());
}