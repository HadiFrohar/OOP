#pragma once
#include "FieldValidator.h"
template<typename T>
class ValidatorTemplate : public FieldValidator
{
public:

	//base class for template validators, used this class to get the option
	//to call the valditing function for different types
	ValidatorTemplate(std::string errorMsg);

	//validating function
	virtual bool validate(const T& item) = 0;

};

template<typename T>
ValidatorTemplate<T>::ValidatorTemplate(std::string errorMsg)
	:FieldValidator(errorMsg)
{
}
