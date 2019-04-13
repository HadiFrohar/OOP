#pragma once
#include "ValidatorTemplate.h"
class NoDigitValidator : public ValidatorTemplate<std::string>
{
public:

	//constructor, it sends the appropriate message to base class
	NoDigitValidator();

	//validates if the name is correct (has no digits)
	bool validate(const std::string& str) override;
};

