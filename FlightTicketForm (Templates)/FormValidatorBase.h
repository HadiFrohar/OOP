#pragma once
#include <vector>
#include <string>
class FormValidatorBase
{
public:

	//base class of field validator - it takes the appropriate error message
	FormValidatorBase(std::string errorMsg);
	virtual bool validate() const = 0 ;

private:
	std::string m_errorMsg;

protected:

	//this vector is used for validating, it contains in each row (based on
	//id of the class\currency) all the destinations that can be with the
	//currency\class
	std::vector<std::vector<int>> m_validtorMatrix;

};
