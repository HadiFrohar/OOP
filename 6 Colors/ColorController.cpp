#include "ColorController.h"
#include <algorithm>

using std::make_pair;

ColorController::ColorController()
{
	//(color, hover_color)
	m_colors.push_back(make_pair(sf::Color(255, 0, 0), sf::Color(220, 20, 60))); //red
	m_colors.push_back(make_pair(sf::Color(255, 165, 0), sf::Color(255, 140, 0))); //orange
	m_colors.push_back(make_pair(sf::Color(204, 204, 0), sf::Color(153, 153, 0))); //yellow
	m_colors.push_back(make_pair(sf::Color(50, 205, 50), sf::Color(127, 255, 0))); //green
	m_colors.push_back(make_pair(sf::Color(30, 144, 255), sf::Color(100, 149, 237))); //blue
	m_colors.push_back(make_pair(sf::Color(255, 20, 147), sf::Color(255, 105, 180))); //pink
	srand((unsigned)time(NULL));

}

const sf::Color & ColorController::getRandomColor() const
{
	return m_colors[rand() % m_colors.size()].first;
}

const unsigned int ColorController::id(const std::pair<sf::Color, sf::Color> & color) const
{
	auto it = std::find(m_colors.begin(), m_colors.end(), color);
	return unsigned(std::distance(m_colors.begin(), it));
	
}

const unsigned int ColorController::id(const sf::Color & color) const
{
	auto it = std::find_if(m_colors.begin(), m_colors.end(), [&color]
	(const std::pair<sf::Color, sf::Color> &p)
		{ return color == p.first; });
	return unsigned(std::distance(m_colors.begin(), it));
}

const std::pair<sf::Color, sf::Color>& ColorController::getColor(const int &id) const
{
	return m_colors[id];
}

const std::pair<sf::Color, sf::Color>& ColorController::getPair(const sf::Color & color) const
{
	return *std::find_if(m_colors.begin(), m_colors.end(), [&](const std::pair<sf::Color, sf::Color> &p)
	{return p.first == color; });
}

const int ColorController::getNumOfcolors() const
{
	return (int)m_colors.size();
}



