#pragma once
#include "Utilities.h"
#include "Board.h"
#include "Rectangle.h"

class IsoscelesTriangle
{
public:

	IsoscelesTriangle();

	/*
	*This function will create a triangle with a specifc details in case the
	* triangle the coordinates the user entered were not good
	*/
	void defaultTriangle();

	/*
	This function will create a triangle based on 3 points
	Arguments: array of 3 points
	*/
	IsoscelesTriangle(const Vertex vertices[3]);

	/*
	This function will calculate the other points of the triangle and create it
	Arguments:center point, width of triangle, height of triangle
	*/
	IsoscelesTriangle(const Vertex& center, double width, double height);

	/*
	This function will get a specific point of triangle
	Arguments:index of point (0,1,2)
	*/
	Vertex getVertex(int index) const;

	/*
	This function will get the base length of the triangle
	*/
	double getLength() const;
	
	/*
	This function will get the length of triangle scale
	*/
	double getScelesLength() const;
	
	/*
	This function will get the height of triangle
	*/
	double getHeight() const;

	/*
	This function will check if a specfic triangle coordinates are in range
	Arguments: 3 points of triangle
	*/
	bool isVaildIn(const Vertex vertices[3]);

	/*
	This function will check if triangle is in range (the coordinates)like above
	*/
	bool isVaild() const;

	/*
	This function will draw the triangle on board
	Arguments: board
	*/
	void draw(Board& board) const;

	/*
	This function will get triangle inside a rectangle
	*/
	Rectangle getBoundingRectangle() const;

	/*
	This function will get the area of triangle
	*/
	double getArea() const;

	/*
	This function will get the premiter of triangle
	*/
	double getPerimeter() const;

	/*
	This function will get the center point of triangle
	*/
	Vertex getCenter() const;

	/*
	This function will scale triangle by a given factor
	Arguments:factor for scale
	*/
	bool scale(double factor);

private:
	//Triangle points
	Vertex m_vertices[3];
};

