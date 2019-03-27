#pragma once
#include "Pixel.h"
class ImageDataStructure
{
public:
	ImageDataStructure(int height = 0, int width = 0); //default cor
	ImageDataStructure(const ImageDataStructure& other); //copy cor, it uses = operator
	~ImageDataStructure(); //destructor, it will free the dynamic memory

	int getHeight() const; //returns height of the image
	int getWidth() const; //returns the width of the image

	//returns a copy of the data that is calling it but resized (with added
	//empty (WHITE) pixels or removed pixels)
	ImageDataStructure resizedImageData(int height, int width) const;


	//updates pixel in index (x,y) color
	void updatePixel(int x, int y, unsigned char color) const;

	//returns color of pixel in index (x,y)
	char getColor(int x, int y) const;

	//the detaisl of the first data will be as the second data,
	//it will free the pixels array, and then create one equals
	//to the second data array and copys the pixels
	ImageDataStructure &operator=(const ImageDataStructure &);

	//the first data will be updated is data1|data2
	//it calls for the | operator of this class
	ImageDataStructure &operator|=(const ImageDataStructure &);

	//the first data will be updated is data1&data2
	//it calls for the & operator of this class
	ImageDataStructure &operator&=(const ImageDataStructure &);


	//the data will be doubled, so each pixel will be doubled (appears two times)
	//it creates a new data with doubled width size and passes the pixels to it
	ImageDataStructure &operator++();

	//the data will be minimzied, only the right pixel in every 2 pixels will be in the
	//it creates a data with width\2
	ImageDataStructure &operator--();

	//it uses the () operator of this class
	const Pixel operator()(int, int) const;

	//it will return the pixel in (x,y) index
	Pixel &operator()(int, int);

	//updates the size of the pixel array, it will first free it from the memory
	//and then creates new pixel array based on what is passed
	void updateSize(int height, int width);

	//friend so it uses private members
	friend std::istream& operator>>(std::istream&, ImageDataStructure&);


private:
	Pixel **m_pixels; //pixels array (dynamic 2d array)
	int m_width; //width
	int m_height; //height

	//frees the dynamic array of the pixels
	void freeMemory();

	//creates a new dynamic array of pixels based on the width and height
	void createArray();

};

//returns the first data connected to the second data, it creates a new data with width
//of the sum of the two widths and height of the maximum height between the two heights
//and then connectes the two images (left image will be on left, right image will be on
//right), empty pixels are empty (WHITE)
ImageDataStructure operator+(const ImageDataStructure &, const ImageDataStructure &);

//returns the first data unioned with second data,* it creates a new data with maximum
//width and height between the two datas, and also resizes the two datas, (to maximum
//width and height) and then moves on each two pixels that are in the same place and
//unions them, the result will be saved in the first created data (*)
ImageDataStructure operator|(const ImageDataStructure &, const ImageDataStructure &);

//returns the first data cutted with second data,* it creates a new data with minimum
//width and height between the two datas, and also resizes the two datas, (to minimum
//width and height) and then moves on each two pixels that are in the same place and
//cuts them, the result will be saved in the first created data (*)
ImageDataStructure operator&(const ImageDataStructure &, const ImageDataStructure &);

//it will do ++data and returns the original data (before doubling it)
ImageDataStructure operator++(ImageDataStructure&, int);

//it will do --data and returns the original data (before minimizign it)
ImageDataStructure operator--(ImageDataStructure&, int);

//returns if the datas details are the same (same height, width and same pixels in every place)
bool operator==(const ImageDataStructure &, const ImageDataStructure &);

//returns the inverse of == operator (!==)
bool operator!=(const ImageDataStructure &, const ImageDataStructure &);


//input operator, it will read line by line and moves on the line getting pixel
// (one by one) and updates it in the pixels array
std::istream& operator>>(std::istream&, ImageDataStructure&);
