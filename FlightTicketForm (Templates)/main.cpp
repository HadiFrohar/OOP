#include <memory>
#include <string>
#include <iostream>
#include <cstdlib> // for system()
#include <cstdint> // for uint32_t
#include <chrono>  // for currentYear() implementation
#include <ctime>   // for currentYear() implementation

//------------------- User includes ----------------------------

// A class that represents a form. A form has many fields
#include "Form.h"

// A class that represents a field. A field can have one or more validator
#include "Field.h"

// A class that represents a range validator.
// It validates if a field value is in some range.
// The type used as template parameter must implement < and > operators.
#include "RangeValidator.h"

// A class that represents a no-digit-characters validator.
// It validates that the field value contains no digits.
// Works only on std::string.
#include "NoDigitValidator.h"

// A class that represents an ID validator.
// ID validation is done using the control digit.
// Works only on the type 'uint32_t'.
#include "IdValidator.h"

// A class that represents a value and his name.
// The class must override the << and >> operators.
// >> operator reads an int and << operator prints destination name if the value is
// valid and if not - the number.
#include "ValuesToNames.h"

// A class that keeps the names of the different destinations
#include "DestinationNames.h"

// A class that keeps the names of the different classes
#include "ClassNames.h"

// A class that keeps the names of the different currencies
#include "CurrencyNames.h"

// A class that represents a destination-vs.-class validator.
// It checks if the destination and class supplied matches each other.
// The types used as template parameter must be Field.

#include "DestinationToClassValidator.h"

// A class that represents a destination-vs.-currency validator.
// It checks if the destination and currency supplied matches each other.
// The types used as template parameter must be Field.

#include "DestinationToCurrencyValidator.h"

//------------------- Function declarations ----------------------------

// Prints welcome message to the given std::ostream
void displayWelcomeMessage(std::ostream& ostr);

// Prints goodbye message to the given std::ostream
void displayGoodbyeMessage(std::ostream& ostr);

// Prints error message to the given std::ostream
void displayErrorMessage(std::ostream& ostr);

// Prints form to the given std::ostream
void displayFormFields(std::ostream& ostr, const Form& form);

// Utility function for clearing the terminal screen
void clearScreen();

// Utility function for getting current year from computer clock
int currentYear();

//------------------- consts --------------------------

const int MAX_POSSIBLE_YEAR = 7;
const int MIN_AGE = 15;
const int MAX_AGE = 120;

//------------------- main ----------------------------

int main()
{
		// Creating the form fields
		auto nameField = std::make_unique<Field<std::string>>("What is your name?");
		auto idField = std::make_unique<Field<uint32_t>>("What is your ID?");
		auto yearOfBirthField = std::make_unique<Field<int>>("What is your year of birth?");
		auto destinationField = std::make_unique<Field<ValuesToNames<DestinationNames>>>("What is your flight destination?\n"
			"(1 - Rome, 2 - Prague, 3 - New York, 4 - India, 5 - Thailand)");


		auto classField = std::make_unique<Field<ValuesToNames<ClassNames>>>("Which class you want?\n"
			"(1 - First Class, 2 - Business Class, 3 - Economy Class)");
		auto currencyField = std::make_unique<Field<ValuesToNames<CurrencyNames>>>("In what currency will you pay?\n"
			"(1 - NIS, 2 - Euro, 3 - Dollar)");

		// Creating the field validators
		auto nameValidator = std::make_unique<NoDigitValidator>();
		auto idValidator = std::make_unique<IdValidator>();
		auto ageValidator = std::make_unique<RangeValidator<int>>(currentYear() - MAX_AGE, currentYear() - MIN_AGE);
		auto destinationValidator = std::make_unique<RangeValidator<ValuesToNames<DestinationNames>>>(1, 5);
		auto classValidator = std::make_unique<RangeValidator<ValuesToNames<ClassNames>>>(1, 3);
		auto currencyValidator = std::make_unique<RangeValidator<ValuesToNames<CurrencyNames>>>(1, 3);



		// Adding the validators to the fields
		nameField->addValidator(nameValidator.get());
		idField->addValidator(idValidator.get());
		yearOfBirthField->addValidator(ageValidator.get());
		destinationField->addValidator(destinationValidator.get());
		classField->addValidator(classValidator.get());
		currencyField->addValidator(currencyValidator.get());
		
		// Creating form validators
		auto destinationToClassValidator
			= std::make_unique<DestinationToClassValidator<Field<ValuesToNames<DestinationNames>>, Field<ValuesToNames<ClassNames>>>>(destinationField.get(), classField.get());
		auto destinationToCurrencyValidator
			= std::make_unique<DestinationToCurrencyValidator<Field<ValuesToNames<DestinationNames>>, Field<ValuesToNames<CurrencyNames>>>>(destinationField.get(), currencyField.get());


		// Creating the form and adding the fields to it
		Form myForm;
		myForm.addField(nameField.get());
		myForm.addField(idField.get());
		myForm.addField(yearOfBirthField.get());
		myForm.addField(destinationField.get());
		myForm.addField(classField.get());
		myForm.addField(currencyField.get());

		// Adding form validators
		myForm.addValidator(destinationToClassValidator.get());
		myForm.addValidator(destinationToCurrencyValidator.get());

		// Getting the information from the user
		clearScreen();
		displayWelcomeMessage(std::cout);

		// Get the input only for empty or not valid fields
		myForm.fillForm();

		// Validation loop
		for (auto formIsCorrect = myForm.validateForm(); !formIsCorrect; formIsCorrect = myForm.validateForm())
		{
			// Displays all form fields with value (and error if not valid)
			clearScreen();
			displayErrorMessage(std::cout);

			displayFormFields(std::cout, myForm);

			myForm.fillForm();
		}

		clearScreen();
		displayGoodbyeMessage(std::cout);
		displayFormFields(std::cout, myForm);
		
	return 0;
}

void displayFormFields(std::ostream& ostr, const Form& form)
{
	ostr << form << '\n';
}

void displayWelcomeMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|                  Hello and welcome!                      |\n"
		"|  In order to register please fill in the fields below    |\n"
		"+----------------------------------------------------------+\n";
}

void displayErrorMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|     There was an error in at least one of the fields!    |\n"
		"|                Please correct the error(s)               |\n"
		"+----------------------------------------------------------+\n";
}

void displayGoodbyeMessage(std::ostream& ostr)
{
	ostr << "+----------------------------------------------------------+\n"
		"|                      Thank you!                          |\n"
		"|               This is the data you sent:                 |\n"
		"+----------------------------------------------------------+\n";
}

void clearScreen()
{
	system("cls");
}

std::tm localtime(const time_t& time)
{
#ifdef _MSC_VER
	std::tm calendarTime = {};
	localtime_s(&calendarTime, &time);
	return calendarTime;
#else
	return *std::localtime(&time);
#endif
}

int currentYear()
{
	using clock = std::chrono::system_clock;
	auto now = clock::to_time_t(clock::now());
	return localtime(now).tm_year + 1900;
}