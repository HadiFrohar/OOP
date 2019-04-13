#pragma once
#include "Field.h"
#include "ValuesToNames.h"
#include "DestinationNames.h"
#include "ClassNames.h"
#include "CurrencyNames.h"
#include "FormValidatorBase.h"

template<typename T1, typename T2>
class FormValidator : public FormValidatorBase
{
public:

	//validates form, it takes two fields and validates them

	//constructor - it takes the approprite error message, two fields
	FormValidator(std::string errorMsg, T1 *firstField, T2 *secondField);

	//returns if they (two fields in the validator) are correct for the form
	bool validate() const;

	//adds row (of indexes) for the vector that is used for validating the field
	void addValRow(std::vector<int> row);

private:

	//fields in validator
	T1 *m_firstField;
	T2 *m_secondField;
};


template<typename T1, typename T2>
FormValidator<T1, T2>::FormValidator(std::string errorMsg, T1 * firstField, T2 * secondField)
	:FormValidatorBase(errorMsg), m_firstField(firstField), m_secondField(secondField)
{
	std::vector<int> emptyRow;
	addValRow(emptyRow);
}

template<typename T1, typename T2>
bool FormValidator<T1, T2>::validate() const
{
		if(m_secondField->getItem().getValue() >= (int) m_validtorMatrix.size())
			return false;
		for (auto &val : m_validtorMatrix[m_secondField->getItem().getValue()])
			if (val == m_firstField->getItem().getValue())
				return true;

		m_firstField->uncorrect();
		m_secondField->uncorrect();

	return false;
}

template<typename T1, typename T2>
void FormValidator<T1, T2>::addValRow(std::vector<int> row)
{
	m_validtorMatrix.push_back(row);
}
