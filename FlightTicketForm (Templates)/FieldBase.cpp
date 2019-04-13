#include "FieldBase.h"


FieldBase::FieldBase(std::string msg)
	:m_msg(msg), m_errorMsg(""), m_validated(false)
{
}

void FieldBase::addValidator(FieldValidator * validator)
{
	m_validators.push_back(validator);
}

std::string FieldBase::getFieldMsg() const
{
	return m_msg;
}



bool FieldBase::validated() const
{
	return m_validated;
}

void FieldBase::printError() const
{
	std::cout << m_errorMsg;
}

void FieldBase::uncorrect()
{
	m_validated = false;
}





std::ostream & operator<<(std::ostream & os, const FieldBase & field)
{
	os << "-------------------------------------------------------------------------\n";
	os << field.getFieldMsg() << " = ";
	field.printItem();
	if (!field.validated())
		field.printError();
	os << std::endl;
	os << "-------------------------------------------------------------------------\n";

	return os;
}
