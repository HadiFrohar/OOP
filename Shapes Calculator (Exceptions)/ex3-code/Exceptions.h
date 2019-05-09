#pragma once
#include<iostream>
using std::exception;

//If user entered an number out of range (for example for maximum shapes in list it it
//will be trigerred if user enterd number bigger than 100)
class OutOfRange : public exception
{
public:
	const char * what() const noexcept {
		return "Error, number is out of range!";
	}
};

//If user tries to add shape to the list while its full (=maximum shapes in list)
class ListIsFull : public exception
{
public:
	const char * what() const noexcept {
		return "Error, list is full, make space in list";
	}
};

//If user enters an unknown command
class NotValidCommand : public exception
{
public:
	const char * what() const noexcept {

		return "Error, command is not valid!";
	}
};

//If user tries to create an undefined shape
class ShapeNotValid : public exception
{
public:
	const char * what() const noexcept {

		return "Error, no appropriate shape!";
	}
};

//If user opening file failed
class FileNotOpen : public exception
{
public:
	const char * what() const noexcept {

		return "Error, couldn't open file!";
	}
};

//If user enters an id that has no shape created (in the vector)
class NoShapeFound : public exception
{
public:
	const char * what() const noexcept {

		return "Error, no shape found with this id!";
	}
};

