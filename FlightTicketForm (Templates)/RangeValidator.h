#pragma once
#include "ValidatorTemplate.h"
#include "ValuesToNames.h"
template<typename T>
class RangeValidator : public ValidatorTemplate<T>
{
public:
	//constructor, it sends the appropriate message to base class and
	//it gets the approprite items based on the arguments that were passed
	RangeValidator(int minimum, int maximum);

	//validates if the passed item is in range (between the items that are
	//saved, or them)
	bool validate(const T& item);

private:
	T m_min; //minimum
	T m_max; //maximum
};

template<typename T>
RangeValidator<T>::RangeValidator(int minimum, int maximum)
	:ValidatorTemplate<T>("\t Out of range")
{
	m_min = T(minimum);
	m_max = T(maximum);
}
template<typename T>
bool RangeValidator<T>::validate(const T& item)
{
	return (item >= m_min && item <= m_max);
	return true;
}
