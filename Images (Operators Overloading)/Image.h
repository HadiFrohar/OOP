#pragma once
#include "ImageDataStructure.h"
class Image
{
public:
	Image(int height = 0, int width = 0); //default contstuctor if image
	Image(const Image& other); //copy constructor of image, it will copy the ImageDataStructure
	~Image(); //destructor of image

	//returns the height of the image
	int GetHeight() const { return m_data.getHeight(); }

	//return the width of the image
	int GetWidth() const { return m_data.getWidth(); }

	//the data structure of the second image will be the data structure of the first image
	//it will call for the = operator of the ImageDataStructre
	Image &operator=(const Image &);

	//the data structure of the second image will be added (connected) to the data
	//structure of the second image it will call for = and + operators of class (Image)
	Image operator+=(const Image &);
	
	//the data structure of the image will be multiplied "n" times
	//it will call for = and * operators of this class (Image)
	Image operator*=(unsigned int);

	//the pixels in the data structure of the first image will be unioned with the second
	//image pixels. it will call for | and = operators of this class (Image)
	Image operator|=(const Image &);

	//the pixels in the data structure of the first image will be cutted with the second
	//image pixels. it will call for & and = operators of this class (Image)
	Image operator&=(const Image &);

	//the width of the image will be doubled, so each pixel will appear two times (each
	//pixel will be doubled), it willl call for the ++ operator of the data
	Image &operator++();

	//the width of the image will be minimized, so between every two pixels, only the
	//right pixel will be in the new image it willl call for the -- operator of the data
	Image &operator--();

	//it will return the pixel that is located at (x,y), it will call for
	//& operator of the ImageDataStructure
	Pixel &operator()(int, int);

	//it will call for the () operator of this (Image) class
	const Pixel operator()(int, int) const;

	//it will check if the images are the same, this mean their data equals, so
	//it will call for the == operator of ImageDataStructure
	bool operator==(const Image &) const;

	//friend operators (so we can access private members)
	friend std::ostream& operator<<(std::ostream& , const Image &);
	friend std::istream& operator>>(std::istream&, Image&);

	//it will return image that its data eqauls to the union of first image data
	//with the second image data, so it will call for | operator in ImageDataStructure
	Image operator|(const Image &);

	//it will return image that its data eqauls to the data of first image connected
	//with second image data, so it will call for | operator in ImageDataStructure
	Image operator+(const Image &);
	//it will return image that its data equals to the data of first image cutted with
	//second image data, so it will call for & operator in ImageDataStructure
	Image operator&(const Image &);

	
private:
	//image data structure, it contains the height, width, pixels of the image
	ImageDataStructure m_data;


};

//it will call for the inverse of == operator (!==)
bool operator!=(const Image &, const Image &);

//it will return image, A*n=A+A+A+...+An, so it will call for + operator n times
Image operator*(const Image &, unsigned int);

//returns same as the above operator, actually it calls for it and returns the result
Image operator*(unsigned int, const Image &);

//it will do ++Image and returns the original image (before doubling it)
Image operator++(Image&, int);

//it will do --Image and returns the original image (before minimizing it)
Image operator--(Image&, int);

//output operator, it will print the image, it will move on all pixels and call for
//the output operator (<<) of the Pixel
std::ostream& operator<<(std::ostream& os, const Image &image);
//it reads height and width, and then calls for >> operator of data to read
//the pixels
std::istream& operator>>(std::istream&, Image&); 
