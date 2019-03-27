#include "ImageDataStructure.h"
#include <string>


ImageDataStructure::ImageDataStructure(int height, int width)
	:m_height(height), m_width(width), m_pixels(nullptr)
{
	createArray();
}

ImageDataStructure::ImageDataStructure(const ImageDataStructure & other)
	:m_height(0), m_width(0), m_pixels(nullptr)
{
	*this = other;
}

ImageDataStructure::~ImageDataStructure()
{
	freeMemory();
}

int ImageDataStructure::getHeight() const
{
	return m_height;
}

int ImageDataStructure::getWidth() const
{
	return m_width;
}

ImageDataStructure ImageDataStructure::resizedImageData(int height, int width) const
{
	ImageDataStructure data(height, width);

	for (int x = 0; x < getHeight(); x++)
		for (int y = 0; y < m_width; y++)
			data.updatePixel(x, y, getColor(x, y));
	
	return data;
}



void ImageDataStructure::updatePixel(int x, int y, unsigned char color) const
{
	m_pixels[x][y].setColor(color);
}

char ImageDataStructure::getColor(int x, int y) const
{
	return m_pixels[x][y].getColor();
}


ImageDataStructure & ImageDataStructure::operator=(const ImageDataStructure &other)
{
	if (this == &other)
		return *this;

	updateSize(other.getHeight(), other.getWidth());


	for (int i = 0; i < getHeight(); i++)
		for (int j = 0; j < getWidth(); j++)
			m_pixels[i][j].setColor(other.getColor(i, j));


	return *this;
}

ImageDataStructure & ImageDataStructure::operator|=(const ImageDataStructure &other)
{

	*this = *this | other;
	return *this;
}

ImageDataStructure & ImageDataStructure::operator&=(const ImageDataStructure &other)
{

	*this = *this&other;
	return *this;

}

ImageDataStructure & ImageDataStructure::operator++()
{
	ImageDataStructure newData(getHeight(), getWidth() * 2);
	int index = 0;
	for (int i = 0; i < getHeight(); i++)
		for (int j = 0, index = 0; j < getWidth(); j++, index+=2)
		{
			newData.updatePixel(i, index, getColor(i, j));
			newData.updatePixel(i, index+1, getColor(i, j));
		}
	*this = newData;
	return *this;
}

ImageDataStructure & ImageDataStructure::operator--()
{
	ImageDataStructure newData(getHeight(), getWidth() / 2);
	int index = 0;
	for (int i = 0; i < getHeight(); i++)
		for (int j = 1, index = 0; j < getWidth(); j += 2, index++)
			newData.updatePixel(i, index, getColor(i, j));



	*this = ImageDataStructure(newData);

	return *this;
}

const Pixel ImageDataStructure::operator()(int x, int y) const
{
	if (x >= getHeight() || y >= getWidth())
	{
		std::cerr << "Out of range";
		exit(EXIT_FAILURE);
	}
	return m_pixels[x][y];
}

Pixel & ImageDataStructure::operator()(int x, int y)
{
	if (x >= getHeight() || y >= getWidth())
	{
		std::cerr << "Out of range";
		exit(EXIT_FAILURE);
	}
	return m_pixels[x][y];
}

void ImageDataStructure::updateSize(int height, int width)
{
	freeMemory();
	m_height = height;
	m_width = width;
	createArray();
}

void ImageDataStructure::createArray()
{

	if (getHeight() > 0 && getWidth() > 0)
	{
		m_pixels = new Pixel*[getHeight()];
		for (int i = 0; i < getHeight(); i++)
			m_pixels[i] = new Pixel[getWidth()];
	}
	else
		m_pixels = nullptr;
}


void ImageDataStructure::freeMemory()
{
	if (m_pixels == nullptr)
		return;

	for (int i = 0; i < getHeight(); i++)
		delete[] m_pixels[i];

	delete[] m_pixels;

	m_pixels = nullptr;
	m_height = 0;
	m_width = 0;
}

ImageDataStructure operator+(const ImageDataStructure &dataToCopy1, const ImageDataStructure &dataToCopy2)
{
	ImageDataStructure data(extractMax(dataToCopy1.getHeight(), dataToCopy2.getHeight()),
		dataToCopy1.getWidth()+dataToCopy2.getWidth());

	for (int i = 0; i < dataToCopy1.getHeight(); i++)
		for (int j = 0; j < dataToCopy1.getWidth(); j++)
			data.updatePixel(i, j, dataToCopy1.getColor(i, j));

	for (int i = 0; i < dataToCopy2.getHeight(); i++)
		for (int j = 0; j < dataToCopy2.getWidth(); j++)
			data.updatePixel(i, j + dataToCopy1.getWidth(), dataToCopy2.getColor(i, j));


	return data;
}

ImageDataStructure operator|(const ImageDataStructure & data1, const ImageDataStructure & data2)
{
	ImageDataStructure data(extractMax(data1.getHeight(), data2.getHeight()),
		extractMax(data1.getWidth(), data2.getWidth()));
	ImageDataStructure tempData1 = data1.resizedImageData(extractMax(data1.getHeight(), data2.getHeight()),
		extractMax(data1.getWidth(), data2.getWidth()));
	ImageDataStructure tempData2 = data2.resizedImageData(extractMax(data1.getHeight(), data2.getHeight()),
		extractMax(data1.getWidth(), data2.getWidth()));

	for (int i = 0; i < data.getHeight(); i++)
		for (int j = 0; j < data.getWidth(); j++)
			data.updatePixel(i, j, (tempData1(i,j) | tempData2(i,j)).getColor());


	return data;
}

ImageDataStructure operator&(const ImageDataStructure &data1, const ImageDataStructure &data2)
{
	ImageDataStructure data(extractMin(data1.getHeight(), data2.getHeight()),
		extractMin(data1.getWidth(), data2.getWidth()));

	for (int i = 0; i < data.getHeight(); i++)
		for (int j = 0; j < data.getWidth(); j++)
			data.updatePixel(i, j, (data1(i, j) & data2(i, j)).getColor());


	return data;
}

ImageDataStructure operator++(ImageDataStructure &data, int)
{
	ImageDataStructure temp(data);
	++data;
	return temp;
}

ImageDataStructure operator--(ImageDataStructure &data, int)
{
	ImageDataStructure temp(data);
	--data;
	return data;

}

bool operator==(const ImageDataStructure &data1, const ImageDataStructure &data2)
{
	if (data1.getHeight() != data2.getHeight() || data1.getWidth() != data2.getWidth())
		return false;
	for (int i = 0; i < data1.getHeight(); i++)
		for (int j = 0; j < data1.getWidth(); j++)
			if (data1(i, j) != data2(i, j))
				return false;

	return true;
}

bool operator!=(const ImageDataStructure &data1, const ImageDataStructure &data2)
{
	return !(data1 == data2);
}

std::istream & operator>>(std::istream &os, ImageDataStructure &data)
{
	std::string inputString;

	for (int i = 0; i < data.getHeight(); i++)
	{
		std::getline(os, inputString);
		for (unsigned j = 0; j < inputString.length(); j++)
		{
			if (i >= data.getWidth())
				break;
			data.updatePixel(i, j, inputString[j]);
		}
	}

	return os;
}


