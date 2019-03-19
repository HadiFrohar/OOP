#pragma once
#include<iostream>
#include "Vertex.h"
#include "macros.h"
#include "Board.h"

class Rectangle
{
public:

	Rectangle();

	/*
	*This function will create a rectangle with a specifc details in case the
	* rectangle the coordinates the user entered were not good
	*/
	void defaultRectangle();

	/*
	*This fucntion will create a reactangle from 2 points
	Arguments: bottom left point, top right point
	*/
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);

	/*
	*This fucntion will create a reactangle from 2 points
	Arguments:array of two points: bottom left point, top right point
	*/
	Rectangle(const Vertex vertices[2]);

	/*
	*This fucntion will create a reactangle from 2 points coordinates
	Arguments: point1: x, y. point2: x, y
	*/
	Rectangle(double x0, double y0, double x1, double y1);

	/*
	*This fucntion will create a reactangle point, width and height of rectangle
	Arguments: bottom left point, width, height
	*/
	Rectangle(const Vertex& start, double width, double height);

	/*
	This will return the bottom left point
	*/
	Vertex getBottomLeft() const;

	/*
	This will return the top right point
	*/
	Vertex getTopRight() const;

	/*
	This will return the width of the rectangle
	*/
	double getWidth() const;

	/*
	This will return rectangle height
	*/
	double getHeight() const;

	/*This will check if two points are in range for rectangle
	Arguments: bottom left point, top right point
	*/
	bool isVaildIn(const Vertex& bottomLeft, const Vertex& topRight);

	/*This will check if rectangle coordinates are in range (good)
	*/
	bool isVaild() const;

	/*
	This will draw rectangle on board
	Arguments: board to draw on
	*/
	void draw(Board& board) const;

	/*
	This will get the rectangle that is blocks the rectangle
	*/
	Rectangle getBoundingRectangle() const;

	/*
	This will get the area of the rectangle
	*/
	double getArea() const;

	/*
	This will get the perimeter of the rectangle
	*/
	double getPerimeter() const;

	/*
	This will get the point in center of the rectangle
	*/
	Vertex getCenter() const;

	/*
	This will scale the rectangle based on the factor that was passed to it
	Arguments: scale factor
	*/
	bool scale(double factor);


private:

	//rectangle points - elements
	Vertex m_bottomLeft;
	Vertex  m_topRight;
};
