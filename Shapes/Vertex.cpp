#include "Vertex.h"
#include "macros.h"

bool Vertex::isHigherThan(const Vertex& other) const
{
    return (m_y > other.m_y);
}

bool Vertex::isRighterThan(const Vertex& other) const
{
    return (m_x > other.m_x);
}

bool Vertex::isEqual(const Vertex & other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

bool Vertex::isValid() const
{
    return m_x >= 0 && m_x <= MAX_X && m_y >= 0 && m_y <= MAX_Y;
}
