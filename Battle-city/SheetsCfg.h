#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "Exceptions.h"

using std::vector;
using std::shared_ptr;
using std::pair;

template <typename T1, typename T2>
class SheetsCfg
{
public:
	SheetsCfg(std::string fileName); //the constructor opens the cfg file then it loads texture file, loads sheets details (IntRects) which all are in the cfg file
	~SheetsCfg();

	T1 &getData(); //returns texture details data (IntRects)

	const sf::Texture &getSheets() const; //return sheets texture

private:

	void loadTexture(); //loads texture
	void readConfig(); //reads sheets data from cfg file (IntRects)
	shared_ptr<sf::IntRect> readData(std::stringstream is); //create IntRect from a line of coordinates (in file)
	T1 m_data; //sheets data (IntRects)
	std::ifstream m_configFile; //configuration file of sheets(file.cfg)

	sf::Texture m_sheetsTexture; //sheets texture

};

template <typename T1, typename T2>
SheetsCfg<T1, T2>::SheetsCfg(std::string fileName)
{
	m_configFile.open(fileName);
	if (!m_configFile.is_open())
		throw FileNotOpen();

	loadTexture();
	readConfig();
}

template <typename T1, typename T2>
SheetsCfg<T1, T2>::~SheetsCfg()
{
	m_configFile.close();
}

template<typename T1, typename T2>
T1 & SheetsCfg<T1, T2>::getData()
{
	return m_data;
}

template<typename T1, typename T2>
const sf::Texture & SheetsCfg<T1, T2>::getSheets() const
{
	return m_sheetsTexture;
}


template<typename T1, typename T2>
void SheetsCfg<T1, T2>::loadTexture()
{
	std::string inputString;
	std::getline(m_configFile, inputString);
	if (!m_sheetsTexture.loadFromFile(inputString))
		throw ConfigError();

}

template <>
inline void SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
	pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>::readConfig()
{

	std::string inputString;
	while (std::getline(m_configFile, inputString))
	{
		if (inputString[0] == '#' || inputString.empty())
			continue;

		auto sprite_a = readData(std::stringstream(inputString));
		std::getline(m_configFile, inputString);
		auto sprite_b = readData(std::stringstream(inputString));

		m_data.emplace_back(std::make_pair(sprite_a, sprite_b));
	}

}


template <>
inline void SheetsCfg<vector<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>,
	vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>::readConfig()
{

	std::string inputString;
	while (std::getline(m_configFile, inputString))
	{
		if (inputString[0] == '#' || inputString.empty())
		{
			m_data.push_back(vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>(0));
			continue;
		}
		auto sprite_a = readData(std::stringstream(inputString));
		std::getline(m_configFile, inputString);
		auto sprite_b = readData(std::stringstream(inputString));

		m_data[m_data.size() - 1].emplace_back(std::make_pair(sprite_a, sprite_b));
	}

}


template <>
inline void SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>::readConfig()
{
	std::string inputString;
	while (std::getline(m_configFile, inputString))
		if (inputString[0] == '#' || inputString.empty())
			continue;
		else
			m_data.emplace_back(readData(std::stringstream(inputString)));
}

template<typename T1, typename T2>
shared_ptr<sf::IntRect> SheetsCfg<T1, T2>::readData(std::stringstream is)
{
	int x, y, width, height;

	if (is >> x >> y >> width >> height)
		return std::make_shared<sf::IntRect>(sf::IntRect(x, y, width, height));
	else
		throw ConfigError();
}
