#pragma once
#include <vector>
#include "FieldBase.h"
#include "FormValidatorBase.h"

class Form
{
public:
	//constructor - updates the error messages of the form
	Form();

	//adds field to the form
	void addField(FieldBase *field);

	//adds form validator to the form (validates two fields)
	void addValidator(FormValidatorBase *validator);

	//fills form, it will go through all the fields in the form and for each
	//field, it will check if its correct (in case the user is correcting), if
	//it is not correct it will ask the user to enter his data
	void fillForm();

	//validates the form, it will go through all the fields, and validate each one
	//(based on each field's validators) and then it will call for the validators of
	//the form
	bool validateForm();

	//output operator - it will print the data and if the errors (if there)
	friend std::ostream& operator<<(std::ostream& os, const Form& form);




private:
	std::vector<FieldBase*> m_fields; //form fields
	std::vector<FormValidatorBase*> m_validators; //form validators
	std::vector<std::string> m_formErrors; //form error messages
};

