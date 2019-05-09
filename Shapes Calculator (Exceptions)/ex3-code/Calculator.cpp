#include "CalculatorItem.h"
#include "Calculator.h"
#include "Add.h"
#include "Subtraction.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Multiply.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Exceptions.h"


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;

string Calculator::getUserCommand()
{
	string act;
	cout << endl << "Please enter a command (\"help\" for command list):" << endl;
	cin >> act;
	return act;
}

void Calculator::runCommand(std::istream &stream, std::string command)
{
	try
	{
		//exit from the calculator
		if (command == "exit")
		{
			exit();
			return;
		}

		//reads commands from file
		else if (command == "read")
			readFile();

		//request for the list of option to action(-to requests)
		else if (command == "help")
			help();

		//prints shapes list
		else if (command == "list")
			printItemList();

		//create a basic shape and put it in the calculator
		else if (command == "cre")
			createShape(stream);

		//calculate the area of a shape from the calculator, the shape is requested by number(-index)
		else if (command == "area")
			calculateArea(stream);

		//calculate the perimeter of a shape from the calculator, the shape is requested by number(-index)
		else if (command == "per")
			calculatePerimeter(stream);

		//create a new shape that consist of multiple of one shape, and put it in the calculator
		else if (command == "mul")
			binaryOperation(std::make_shared<Multiply>(stream, *this));

		//create a new shape that consist of add of one shape and another shape, and put it in the calculator
		else if (command == "add")
			binaryOperation(std::make_shared<Add>(stream, *this));


		//create a new shape that consist of subtraction of one shape from another shape, and put it in the calculator
		else if (command == "sub")
			binaryOperation(std::make_shared<Subtraction>(stream, *this));

		//Draws the shape (regardless of its actual size)
		else if (command == "draw")
			drawItem(stream);

		//Prints all indexes of the shapes that are equal in their area and perimeter to the selected shape
		else if (command == "same")
			findAllSameShapes(stream);

		//Deletes the required shape from the calculator and arranges the indexes of the other shapes
		else if (command == "del")
			deleteItem(stream);

		//Finds and prints the largest of the shapes in the calculator, according to the user selection
		else if (command == "min")
			findMin(stream);

		//Finds and prints the smallest of the shapes in the calculator, according to the user selection
		else if (command == "max")
			findMax(stream);

		//Resizes the maximum amount of shapes
		else if (command == "resize")
			resize(stream);
		else
			throw NotValidCommand();
	}
	catch(...)
	{
		throw;
	}
}

void Calculator::exit()
{
	cout << "Goodbye.";
}

void Calculator::calculateArea(std::istream &stream)
{
	try
	{
		const int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size())
			throw NoShapeFound();
		cout << "Area ";
		m_calculatorItems[index]->printDetails();
		cout << " = " << m_calculatorItems[index]->area() << endl;
	}
	catch (...)
	{
		throw;
	}

}

void Calculator::calculatePerimeter(std::istream &stream)
{
	try
	{
		const int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size() || index < 0)
			throw NoShapeFound();
		cout << "Perimeter ";
		m_calculatorItems[index]->printDetails();
		cout << " = " << m_calculatorItems[index]->perimeter() << endl;
	}
	catch (...)
	{
		throw;
	}
}

void Calculator::drawItem(std::istream &stream)
{
	try
	{
		const int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size())
			throw NoShapeFound();
		m_calculatorItems[index]->draw();

	}
	catch (...)
	{
		throw;
	}
}
void Calculator::findAllSameShapes(std::istream &stream) const
{
	try
	{
		const int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size())
			throw NoShapeFound();
		same(index);
	}
	catch (...)
	{
		throw;
	}
}

void Calculator::deleteItem(std::istream &stream)
{
	try
	{
		const int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size() || index < 0)
			throw NoShapeFound();
		m_calculatorItems.erase(m_calculatorItems.begin() + index);

	}
	catch (...)
	{
		throw;
	}
}

void Calculator::findMin(std::istream &stream) const
{
	try {
		const int amount = Utils::readInt(stream);
		if (amount > m_calculatorItems.size())
			throw OutOfRange();
		//in first time (for Comparison)
		int index = Utils::readInt(stream);
		if (index >= m_calculatorItems.size())
			throw NoShapeFound();
		double min = m_calculatorItems[index]->area();

		for (int i = 0; i < amount - 1; i++)
		{
			index = Utils::readInt(stream);
			if (index >= m_calculatorItems.size())
				throw NoShapeFound();
			min = m_calculatorItems[index]->area() < min ? m_calculatorItems[index]->area() : min;
		}
		cout << "The minimum area is:" << min << endl;
	}
	catch (...)
	{
		throw;
	}
}

void Calculator::findMax(std::istream & stream) const
{
	try
	{
		const int amount = Utils::readInt(stream);
		if (amount > m_calculatorItems.size())
			throw OutOfRange();
		//Calculates the largest area of all selected shapes, return the index of the maxim
		double max = 0;
		for (int i = 0; i < amount; i++)
		{
			const int index = Utils::readInt(stream);
			if (index >= m_calculatorItems.size())
				throw NoShapeFound();
			max = m_calculatorItems[index]->area() > max ? m_calculatorItems[index]->area() : max;
		}
		cout << "The maximum area is:" << max << endl;
	}
	catch(...)
	{
		throw;
	}
}

//the main function in this class, performs actions at user request
void Calculator::run()
{
	updateMaxSize(cin);
	while (true)
	{
		//the user request is in the form of string
		auto command = getUserCommand();
		try
		{
			runCommand(cin, command);
		}
		catch(exception &e)
		{
			cout << e.what() << endl;
		}
	}
}

std::shared_ptr<CalculatorItem> Calculator::operator[](int index) const
{
	if (index < 0 || index >= m_calculatorItems.size())
		throw NoShapeFound();
	return m_calculatorItems[index];
}

//--------------------------------------------------------
//Prints a help screen with a list of possible commands and a brief explanation of it
void Calculator::help()
{
	cout << "Following is the list of the calculator's available commands" << endl
		<< "read file-path - reads file of commands" << endl
		<< "resize - resizes list size"
		<< "list - prints shapes list" << endl
		<< "cre(ate) #shape <R - rectangle | T-triangle | C- circle>" << endl
		<< "area num - Computes the area of shape #num" << endl
		<< "per(imeter) num - Computes the perimeter of shape #num" << endl
		<< "draw num - Draw the shape" << endl
		<< "#num mul(tiply) num x - Creates an item that is the multiplication of shape #num x times" << endl
		<< "add num1 num2 - Creates an item that is the sum of item #num1 and function #num2" << endl
		<< "sub num1 num2 - Creates an item that is the subtraction of item #num1 and function #num2" << endl
		<< "min n #num1-#numN - Returns the smallest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "max n #num1-#numN - Returns the biggest area in the chosen shapes. n - the requested shapes: #num1..." << endl
		<< "same num - Returns shapes with which have the same area and perimeter to the shape #num" << endl
		<< "del(ete) num - Deletes item #num from function list" << endl
		<< "help - Prints this help screen" << endl
		<< "exit - Exits the program." << endl;
}
void Calculator::readFile()
{
	string inputString,
		command;
	cout << "Enter file path (with filetype): ";
	cin >> inputString;
	std::ifstream commandsFile;

	try
	{
		commandsFile.open(inputString);
		if (!commandsFile)
			throw FileNotOpen();
	}
	catch (...)
	{
		throw;
	}


	while (getline(commandsFile, inputString))
	{
		try
		{
			cout << inputString << endl;
			std::istringstream stream(inputString);
			stream >> command;
			runCommand(stream, command);
		}
		catch (exception &e)
		{
			cout << e.what() << endl;
			cout << "Would you like to continue the rest of the commands? (Y to continue): ";
			char answer = toupper(Utils::readChar(cin));
			if (answer == 'Y')
				continue;
			else
				break;
		}
	}

}
//--------------------------------------------------------
//Prints all indices of the shapes that are equal in their area and scope to the selected shape
void Calculator::same(int index) const
{
	const double area = m_calculatorItems[index]->area();
	const double perimeter = m_calculatorItems[index]->perimeter();
	
	for (auto i = 0; i < m_calculatorItems.size(); ++i)
	{
		if (m_calculatorItems[i]->area() == area 
			&& m_calculatorItems[i]->perimeter() == perimeter
			&& i != index)
		{
			cout << i << ": ";
			m_calculatorItems[i]->printDetails();
			cout << endl;
		}
	}
	cout << endl;
}


//-----------------------------------------------------------
//create new shape rectangle/circle/triangle and insert to the list of the shapes (to the vector)
void Calculator::createShape(std::istream &stream)
{
	char shape;
	stream >> shape;
	shape = toupper(shape);
	try {
		if (m_maxShapes <= m_calculatorItems.size())
			throw ListIsFull();
		else if (shape == 'R')
		{
			m_calculatorItems.push_back(std::make_shared<Rectangle>(stream));
		}
		else if (shape == 'C')
		{
			m_calculatorItems.push_back(std::make_shared<Circle>(stream));
		}
		else if (shape == 'T')
		{
			m_calculatorItems.push_back(std::make_shared<Triangle>(stream));
		}
		else
		{
			throw ShapeNotValid();
		}
	}
	catch(...)
	{
		throw;
	}
}
//-----------------------------------------------------------
//print the list of the shapes that in the vector
void Calculator::printItemList() const
{
	int i = 0;
	cout << "\nThis is the shapes list:" << endl;
	for (auto& item : m_calculatorItems)
	{
		cout << i++ << ": ";
		item->printDetails();
		cout << endl;
	}
	cout << "	Items in list: " << m_calculatorItems.size() << "/" << m_maxShapes << endl;
}

void Calculator::resize(std::istream &stream)
{
	try
	{
		updateMaxSize(stream);
	}
	catch (...) {
		throw;
	}

	//checks if the items in list are more than the max size, if yes it will ask the user to remove
	//last items in list or enter new size
	if (m_maxShapes < m_calculatorItems.size())
	{
		char answer;
		cout << "Size is smaller than the items in the list, would you like to remove the last " <<
			m_calculatorItems.size() - m_maxShapes << " items?" << endl;
		cout << "Enter Y to remove, or anything else to choose another size: ";
		answer = toupper(Utils::readChar(stream));
		if (answer == 'Y')
			removeLastItems();
		else
			return resize(stream);
	}
}

void Calculator::updateMaxSize(std::istream &stream)
{
	bool correctSize = false;
	while(!correctSize)
	try {
		cout << "What is the maximum shapes in list? (0-100): ";
		m_maxShapes = Utils::readInt(stream);
		if (m_maxShapes > 100 || m_maxShapes <= 0)
			throw OutOfRange();
		correctSize = true;
	}
	catch (exception &e)
	{
		if (&stream != &cin)
			throw;
		cout << e.what() << endl;
	}
}

void Calculator::removeLastItems()
{
	for (size_t i = 0; i < m_calculatorItems.size() - m_maxShapes;)
		m_calculatorItems.pop_back();
}

void Calculator::binaryOperation(std::shared_ptr<CalculatorItem> item)
{
	if (m_maxShapes <= m_calculatorItems.size())
		throw ListIsFull();
	else
		m_calculatorItems.push_back(item);
}
