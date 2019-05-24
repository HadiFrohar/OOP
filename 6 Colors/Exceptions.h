#pragma once
#include<iostream>
using std::exception;
class FileNotOpen : public exception
{
public:
	const char * what() const noexcept {
		return "Error, couldn't load file!";
	}
};