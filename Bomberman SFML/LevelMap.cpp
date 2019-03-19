#include "LevelMap.h"
#include "Utilities.h"


LevelMap::LevelMap()
{

}


LevelMap::~LevelMap()
{
}

bool LevelMap::readMap()
{

	clear();

	std::string inputString;

	while (getline(m_file, inputString))
	{
		//this loop to skip the empty lines in the file.
		while (inputString.empty())
			if (!getline(m_file, inputString))
				break;

		m_map.clear();

		if (inputString.empty())
			return false;

		getSettings(inputString);
		addMapToVector();

		if (!validMap())
			continue;

		if (m_map.size() == 0)
			return false;

		inputString.clear();

		return true;
	}

	return false;

}

void LevelMap::getSettings(std::string firstLine)
{
	std::stringstream stream(firstLine);

	stream >> m_size;

	if (stream.rdbuf()->in_avail() == 0)
		m_levelTime = DEFAULTLEVELTIME;
	else
		stream >> m_levelTime;

	if (stream.rdbuf()->in_avail() == 0)
		m_bombsCount = DEFAULTBOMBSCOUNT;
	else
		stream >> m_bombsCount;

	m_levelTime *= MINUTE;
}

void LevelMap::clear()
{
	m_map.clear();
	m_size = 0;
	m_bombsCount = 0;
	m_levelTime = 0;
}

void LevelMap::addMapToVector()
{
	std::string inputString;
	for (unsigned int i = 0; i < m_size; i++)
	{
		getline(m_file, inputString);
		m_map.push_back(inputString);
	}
}

bool LevelMap::validMap()
{
	for (size_t i = 0; i < m_size; i++)
		if (m_map[0][i] != WALL || m_map[m_map.size() - 1][i] != WALL || m_map[i][0] != WALL || m_map[i][m_map.size() - 1] != WALL)
			return false;

	bool robotFound = false,
		doorFound = false;

	for(unsigned i=0; i<m_size; i++)
		for (unsigned j = 0; j < m_size; j++)
		{
			if (robotFound && m_map[i][j] == ROBOT)
				return false;
			else if (doorFound && m_map[i][j] == DOOR)
				return false;

			if (m_map[i][j] == ROBOT)
				robotFound = true;
			else if (m_map[i][j] == DOOR)
				doorFound = true;
		}

	if (!robotFound || !doorFound)
		return false;

	return true;
}

void LevelMap::openFile()
{
	m_file.open(MAPPATH);
	if (!m_file)
		loadCrash();
}

void LevelMap::closeFile()
{
	m_file.close();
}

std::vector<std::string> &LevelMap::getMap()
{
	return m_map;
}

unsigned int &LevelMap::getSize()
{
	return m_size;
}

unsigned int &LevelMap::getTime()
{
	return m_levelTime;
}

unsigned int &LevelMap::getBombsCount()
{
	return m_bombsCount;
}
