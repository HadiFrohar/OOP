#include "NoDigitValidator.h"


NoDigitValidator::NoDigitValidator()
	:ValidatorTemplate<std::string>("\t Can't contain digits")
{
}

bool NoDigitValidator::validate(const std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (isdigit(str[i]))
			return false;
	return true;
}
