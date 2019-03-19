#pragma once
#include "IsoscelesTriangle.h"
#include "Board.h"
class Kite
{
public:
	
	Kite();

	/*
	*This function will create a kite with a specifc details in case the
	* kite the coordinates the user entered were not good
	*/
	void defaultKite();

	/*
	*This fucntion will create from two triangles
	Arguments: two triangles - the elements needed for kite
	*/
	Kite(const IsoscelesTriangle triangles[2]);


	/*
	*This fucntion will create from a the top point, width of the triangle
	and the height of the bottom and top triangle and create a kite
	Arguments: point of the top, width of triangle, bottom height, top height
	*/
	Kite(const Vertex& top, double width, double topHeight, double bottomHeight);

	/*
	This function will get the height of kite
	*/
	double getTotalHeight() const;

	/*
	This function will check if a specfic kite elements are in range
	Arguments: 2 triangles - elements of kite
	*/
	bool isVaildIn(const IsoscelesTriangle triangles[2]);

	/*
	This function will draw the kite on the board
	Arguments: board that to draw on
	*/
	void draw(Board& board) const;

	/*
	This function will get the bounding rectangle that has the kite
	*/
	Rectangle getBoundingRectangle() const;

	/*
	This function will calculate the area of the kite
	*/
	double getArea() const;

	/*
	This function will calculate the perimeter of the kite
	*/
	double getPerimeter() const;

	/*
	This function will get the point that in center of the kite
	*/
	Vertex getCenter() const;

	/*
	This function will scale the kite from the center baesed on the factor that
	was entered
	Arguments: factor to scale
*/
	bool scale(double factor);


private:

	//kite elements - two triangles
	IsoscelesTriangle m_triangles[2];
};

