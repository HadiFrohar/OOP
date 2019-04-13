#include "Form.h"

Form::Form()
{
	m_formErrors.push_back("Destination and class don't match");
	m_formErrors.push_back("Destination and currency don't match");
}

void Form::addField(FieldBase * field)
{
	m_fields.push_back(field);
}

void Form::addValidator(FormValidatorBase * validator)
{
	m_validators.push_back(validator);
}

void Form::fillForm()
{
	for (auto &field : m_fields)
	{
		if (field->validated())
			continue;
		std::cout << field->getFieldMsg() << std::endl;
		field->readItem();
	}
}

bool Form::validateForm()
{
	for (auto &field : m_fields)
		if (!field->validated())
			return false;
	for (auto &validator : m_validators)
		if (!validator->validate())
			return false;

	return true;
}

std::ostream & operator<<(std::ostream & os, const Form & form)
{
	for (auto& field : form.m_fields)
		os << *field;
	for (size_t i = 0; i < form.m_formErrors.size(); i++)
		if(!form.m_validators[i]->validate())
			std::cout << form.m_formErrors[i] << std::endl;
	return os;
}
