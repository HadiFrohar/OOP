#include "FieldValidator.h"

FieldValidator::FieldValidator(std::string errorMsg)
	:m_errorMsg(errorMsg)
{
}

std::string FieldValidator::getErrorMsg() const
{
	return m_errorMsg;
}
