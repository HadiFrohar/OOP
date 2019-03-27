#include "Pixel.h"


Pixel::Pixel(unsigned char color)
	: m_color(color) {}


unsigned char Pixel::getColor() const
{
	return m_color;
}

Pixel & Pixel::operator|=(const Pixel & p)
{
	if (p.getColor() > m_color)
		setColor(p.getColor());
	return *this;
}

Pixel & Pixel::operator&=(const Pixel & p)
{
	if (p.getColor() < getColor())
		setColor(p.getColor());
	return *this;
}

void Pixel::setColor(unsigned char color)
{
	m_color = color;
}

bool operator==(const Pixel & p1, const Pixel & p2){
	return (p1.getColor() == p2.getColor());
}


bool operator!=(const Pixel & p1, const Pixel & p2){
	return (p1 == p2);
}

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	os << p.getColor();
	return os;
}

Pixel operator|(const Pixel & p1, const Pixel &p2)
{
	if (p1.getColor() >= p2.getColor())
		return Pixel(p1.getColor());
	else
		return Pixel(p2.getColor());
}

Pixel operator&(const Pixel & p1, const Pixel &p2)
{
	if (p1.getColor() <= p2.getColor())
		return Pixel(p1.getColor());
	else
		return Pixel(p2.getColor());
}