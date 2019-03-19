#pragma once

struct Vertex
{
	double m_x;
	double m_y;

	bool isHigherThan(const Vertex& other) const;
	bool isRighterThan(const Vertex& other) const;
	bool isEqual(const Vertex& other) const;
	bool isValid() const;
};
