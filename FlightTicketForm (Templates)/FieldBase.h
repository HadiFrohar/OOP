#pragma once
#include "FieldValidator.h"
#include <iostream>
#include <vector>
class FieldBase
{
public:
	FieldBase(std::string msg); //Field constructor, it gets the question as argument
	void addValidator(FieldValidator* validator); //adds validator to field
	std::string getFieldMsg() const; //returns field message (question)
	virtual void readItem() = 0; //reads an item to the field
	bool validated() const; // returns if the item in field is correct or not
	virtual void printItem() const = 0; //prints the item in the field
	void printError() const; //prints the appropriate error (in case the item is not correct)
	void uncorrect(); //states that the field is not correct (or doesn't fit the form)
private:
	std::string m_msg; //field message (question)
	virtual void validate() = 0; //validates field item, checks if its correct

protected:
	std::vector<FieldValidator *> m_validators; //field validators
	bool m_validated; //states if the item is correct or not
	std::string m_errorMsg; //error message to be printed in case the item is not correct


};

//output operator, it prints the question, user input, error message (if needed)
std::ostream& operator<<(std::ostream& os, const FieldBase& field);
