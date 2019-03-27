#include "Image.h"



Image::Image(int height, int width)
	:m_data(ImageDataStructure(height, width)) {
}


Image::Image(const Image & other)
	: m_data(ImageDataStructure(0,0))
{
	*this = other;
}

Image::~Image()
{
}

Image & Image::operator=(const Image &other)
{
	if (this == &other)
		return *this;

	m_data = other.m_data;
	return *this;
}

bool Image::operator==(const Image & other) const
{
	return m_data == other.m_data;
}

bool operator!=(const Image & img1, const Image & img2)
{
	return !(img1 == img2);
}


Image Image::operator+(const Image & other)
{

	Image img(extractMax(GetHeight(), other.GetHeight()),
		GetWidth() + other.GetWidth());

	img.m_data = m_data + other.m_data;
	return img;
}

Image Image::operator&(const Image &other)
{
	Image img;
	img.m_data = m_data & other.m_data;
	return img;
}

Image operator++(Image &img, int)
{
	Image temp(img);
	++img;
	return temp;
}

Image operator--(Image &img, int)
{
	Image temp(img);
	--img;
	return temp;
}

Image Image:: operator+=(const Image & img2)
{
	*this = *this + img2;

	return *this;
}

Image Image::operator*=(unsigned int num)
{
	*this = *this*num;
	return *this;
}

Image Image::operator|=(const Image &other)
{
	*this = *this | other;
	return *this;
}

Image Image::operator&=(const Image &img)
{
	*this = *this&img;
	return *this;
}

Image & Image::operator++()
{
	++m_data;
	return *this;
}

Image & Image::operator--()
{
	--m_data;
	return *this;
}

Pixel & Image::operator()(int x, int y)
{

	return m_data(x, y);
}

const Pixel Image::operator()(int x, int y) const
{
	return m_data(x, y);
}

std::ostream& operator<<(std::ostream& os, const Image &image)
{

	for (int i = 0; i < image.GetHeight(); i++)
	{
		for (int j = 0; j < image.GetWidth(); j++)
			os << image(i,j) << ' ';
		
		os << std::endl;
	}


	return os;
}

std::istream& operator>>(std::istream& os, Image& image)
{
	int height = 0,
		width = 0;
	std::string inputString;

	os >> height >> width;
	if (os.fail())
	{
		os.clear();
		os.ignore(INT_MAX, '\n');
	}
	//image.m_data.~ImageDataStructure();
	image.m_data = ImageDataStructure(height, width);

	os >> image.m_data;

	return os;
}

Image Image::operator|(const Image & other)
{
	Image img;
	img.m_data = m_data | other.m_data;

	return img;
}

Image operator*(const Image &srcImg, unsigned int num)
{
	Image img;
	for (unsigned i = 0; i < num; i++)
		img += srcImg;

	return img;
}

Image operator*(unsigned int num, const Image &srcImg)
{
	return srcImg * num;
}

