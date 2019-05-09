#pragma once
#include <vector>
#include <memory>
#include <string>

class CalculatorItem;

class Calculator
{
public:
	Calculator() = default;
	~Calculator() = default;
	void run(); //runs the calcualtor (main function of the object)
	std::shared_ptr<CalculatorItem> operator[](int index) const; //returns the shape in that index
private:
	std::vector<std::shared_ptr<CalculatorItem>> m_calculatorItems; //stores shapes
	static std::string getUserCommand(); //command function
	void runCommand(std::istream &stream, std::string command); //runs the command
	static void exit(); //prints goodbye
	static void help(); //prints the available commands and instruction
	void readFile(); //reads file
	void calculateArea(std::istream &); //calculates shape's area
	void calculatePerimeter(std::istream &); //calcualtes shape's perimeter
	void drawItem(std::istream &); //draws shape
	void findAllSameShapes(std::istream &) const; //calls for same function
	void deleteItem(std::istream &); //delets shape from list (calculatorItems)
	void findMin(std::istream &) const; //finds the shape that has the minimum area
	void findMax(std::istream &) const; //finds the shape that has the maximum area
	void same(int index) const; //prints shapes that has same area or perimeter of an shape
	void createShape(std::istream &); //creates shape (R T C)
	void printItemList() const; //print items in list and size of list
	void resize(std::istream &); //resize list of items
	void updateMaxSize(std::istream &); //updates the size of the list
	void removeLastItems(); //removes last items in list (that are out of size)
	void binaryOperation(std::shared_ptr<CalculatorItem> item); //adds binary-operation result to list


	int m_maxShapes; //max amount of shapes in list

};

