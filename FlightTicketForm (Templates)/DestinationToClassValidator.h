#pragma once
#include "FormValidator.h"
template <typename T1 = Field<ValuesToNames<DestinationNames>>, typename T2 = Field<ValuesToNames<ClassNames>>>
class DestinationToClassValidator : public FormValidator<T1, T2>
{
public:

	//this class validates between two fields

	//constructor - it takes two fields, updates the valid vector that we use
	//to check if the fields are making a correct form, it is for destination
	//and class fields
	DestinationToClassValidator(T1 *firstField, T2 *secondField);
};

template<typename T1, typename T2>
DestinationToClassValidator<T1, T2>::DestinationToClassValidator(T1 * firstField, T2 * secondField)
	:FormValidator<T1, T2>("\nDestination and class don't match", firstField, secondField)
{
	std::vector<int> firstClassDes = { 1, 2, 3 };
	std::vector<int> businessClassDes = { 1,2,3,4,5 };
	std::vector<int> economyClassDes = { 3,4,5 };
	
	this->addValRow(firstClassDes);
	this->addValRow(businessClassDes);
	this->addValRow(economyClassDes);

}
