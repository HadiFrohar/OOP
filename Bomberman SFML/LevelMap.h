#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class LevelMap
{
public:
	LevelMap();
	~LevelMap();
	bool readMap();
	//This function gets the settings of the level
	void getSettings(std::string firstLine);

	void clear();

	void addMapToVector();

	//this function checks if the map is valid
	bool validMap();

	void openFile();
	void closeFile();

	std::vector<std::string> &getMap();
	unsigned int &getSize();
	unsigned int &getTime();
	unsigned int &getBombsCount();
	

private:
	std::vector<std::string> m_map; //vector that contains the map
	std::ifstream m_file; //the file used for the map (board.bomb)
	unsigned int m_size, //size of map NXN
		m_levelTime, //max time for the level
		m_bombsCount; //bombs count of the level
};

