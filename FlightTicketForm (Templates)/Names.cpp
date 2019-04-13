#include "Names.h"


void Names::addName(std::string name)
{
	m_names.push_back(name);
}

std::string Names::getName(int i) const
{
	if (i >= m_names.size() || i < 0)
		return std::to_string(i);
	else
		return m_names[i];
}
