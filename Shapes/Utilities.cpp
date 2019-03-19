#include "Utilities.h"
#include <cmath>

bool doubleEqual(double a, double b)
{
    return std::abs(a - b) <= 1;
}

// Some helper functions for addLine()
double distance(const Vertex& v1, const Vertex& v2)
{
    return std::sqrt(std::pow((v1.m_x - v2.m_x), 2)
                     + std::pow((v1.m_y - v2.m_y), 2));
}

bool sameX(const Vertex& v1, const Vertex& v2)
{
    return doubleEqual(v1.m_x, v2.m_x);
}

bool sameY(const Vertex& v1, const Vertex& v2)
{
    return doubleEqual(v1.m_y, v2.m_y);
}

bool operator<(const Vertex& lhs, const Vertex& rhs)
{
    Vertex origin = {0, 0};
    return distance(lhs, origin) < distance(rhs, origin);
}

Vertex setPoint(double x, double y)
{

	Vertex point;
	point.m_x = x;
	point.m_y = y;
	return point;

}