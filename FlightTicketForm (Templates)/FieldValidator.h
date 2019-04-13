#pragma once
#include <string>


class FieldValidator
{
public:

	//this is the base of fields validators

	//constructor-it takes the appropriate error message
	FieldValidator(std::string errorMsg);

	//returns the appropriate error message (specfic error based on validator)
	std::string getErrorMsg() const;

private:
	//error message of the field
	std::string m_errorMsg;
};

