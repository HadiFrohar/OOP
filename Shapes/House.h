#pragma once
#include "Rectangle.h"
#include "IsoscelesTriangle.h"
class House
{
public:

	House();

	/*
	*This function will create a house with a specifc details in case the
	* house the coordinates the user entered were not good
	*/
	void defaultHouse();


	/*
	*This fucntion will create from a triangle and Rectangle
	Arguments: rectangle, triangle - the two elemtns needed for house
	*/
	House(const Rectangle& rectangle, const IsoscelesTriangle& triangle);

	/*
	*This fucntion will create from a the top point, width of the house and the height
	*of the roof and the width of the base of the roof.
	Arguments: point of the top of roof, width of house, triangle height, rectangle height
	*/
	House(const Vertex& roofTop, double width, double roofHeight, double baseHeight);

	/*
	This function will extend the roof width, if successful will return true, otherwise false
	Arguments: extendtion width
	*/
	bool extendRoof(double width);

	/*
	This function will get the height of the house from top to base.
	*/
	double getHeight() const;

	/*
	This function will calculate the difference between roof width and base width of house
	*/
	double getWidthDifference() const;

	/*
	This function will check if the house has valid elemtns or not
	Arguments: house elements
	*/
	bool isVaild(Rectangle rectangle, IsoscelesTriangle triangle);

	/*
	This function will draw the house on the board
	Arguments: board that to draw on
	*/
	void draw(Board& board) const;

	/*
	This function will get the bounding rectangle that has the house
	*/
	Rectangle getBoundingRectangle() const;

	/*
	This function will calculate the area of the house
	*/
	double getArea() const;

	/*
	This function will calculate the preimeter of the house
	*/
	double getPerimeter() const;

	/*
	This function will get the point that in center of the house
	*/
	Vertex getCenter() const;

	/*
	This function will scale the house from the center baesed on the factor that
	was entered
	Arguments: factor to scale
	*/
	bool scale(double factor);


private:

	//House elements
	Rectangle m_rectangle;
	IsoscelesTriangle m_triangle;

};

