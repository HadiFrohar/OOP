#pragma once
#include "Settings.h"
class Pixel
{
public:
	Pixel(unsigned char color = WHITE); //default constructor
	unsigned char getColor() const; //returns the color of the pixel

	//if the second pixel color is darker then the color of the first pixel will be
	//as the color of the second
	Pixel &operator|=(const Pixel &);

	//if the second pixel color is lighter then the color of the first pixel will be
	//as the color of the second
	Pixel &operator&=(const Pixel &);

	void setColor(unsigned char); //sets the color of the pixel



private:
	unsigned char m_color; //pixel color
};

//returns if colors of the pixels are the same
bool operator==(const Pixel &, const Pixel &);
//returns if colors of the pixels are not the same, it will call == operator
bool operator!=(const Pixel &, const Pixel &);

//output operator, it will print the pixel on the output stream
std::ostream& operator<<(std::ostream& , const Pixel& );

//union operator, it will union first pixel with second pixel which means it will
//returns the darker color pixel
Pixel operator|(const Pixel &, const Pixel &);

//cut operator, it will cut first pixel with second pixel which means it will
//returns the lighter color pixel
Pixel operator&(const Pixel &, const Pixel &);