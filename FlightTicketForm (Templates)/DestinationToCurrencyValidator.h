#pragma once
#include "FormValidator.h"
template <typename T1 = Field<ValuesToNames<DestinationNames>>, typename T2 = Field<ValuesToNames<CurrencyNames>>>
class DestinationToCurrencyValidator : public FormValidator<T1, T2>
{
public:

	//this class validates between two fields

	//constructor - it takes two fields, updates the valid vector that we use
	//to check if the fields are making a correct form, it is for destination and
	//currency fields
	DestinationToCurrencyValidator(T1 *firstField, T2 *secondField);
};

template<typename T1, typename T2>
DestinationToCurrencyValidator<T1, T2>::DestinationToCurrencyValidator(T1 * firstField, T2 * secondField)
	:FormValidator<T1, T2>("\nDestination and currency don't match", firstField, secondField)
{
	std::vector<int> nis = { 1, 2, 3, 4, 5 };
	std::vector<int> euro = { 1, 2 };
	std::vector<int> dollar = { 3 };
	this->addValRow(nis);
	this->addValRow(euro);
	this->addValRow(dollar);
}
