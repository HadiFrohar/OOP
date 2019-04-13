#pragma once
#include "FieldBase.h"
#include "ValidatorTemplate.h"
#include <string>
template <typename T>
class Field : public FieldBase
{
public:
	//constructor, it takes the message (question)
	Field(std::string msg);

	//reads item from the user (input function)
	void readItem() override;

	//print field item (output function)
	void printItem() const override;

	//returns the item stored in the field
	const T &getItem();

private:
	T m_item; //item stored in the field

	//validates field using the validators that were sent to the field,
	//it also updates the error message of the field (based on the validator)
	void validate();

};

template<typename T>
Field<T>::Field(std::string msg)
	:FieldBase(msg)
{ }

template<typename T>
void Field<T>::readItem()
{

	std::cin >> m_item;
	/*while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Wrong input, please enter digits\n";
		std::cin >> m_item;
	}*/
	validate();
}

template<>
void Field<std::string>::readItem()
{

	m_item.clear();
	while (m_item.empty())
		std::getline(std::cin, m_item);

	validate();

}


template<typename T>
void Field<T>::printItem() const
{
	std::cout << m_item;
}

template<typename T>
const T & Field<T>::getItem()
{
	return m_item;
}

template<>
void Field<std::string>::printItem() const
{
	std::cout << m_item;
}



template<typename T>
void Field<T>::validate()
{
	for (auto &validator : m_validators)
		if (!((ValidatorTemplate<T>*)(validator))->validate(m_item))
		{
			m_validated = false;
			m_errorMsg = ((ValidatorTemplate<T>*)(validator))->getErrorMsg();
			return;
		}
	m_validated = true;
}
