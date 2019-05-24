#include "Player.h"
#include <algorithm>

Player::Player(std::string name)
	:m_name(name)
{
}

void Player::addShape(std::shared_ptr<Shape> & shape)
{
	m_shapes.push_back(shape);
}

void Player::updateColor(const std::pair<sf::Color, sf::Color> & color)
{
	m_usedColor = color;
	switchColor();
}

void Player::switchColor()
{
	for (auto &shape : m_shapes)
		shape->updateColor(m_usedColor.first);
}

const std::pair<sf::Color, sf::Color> & Player::getUsedColor() const
{
	return m_usedColor;
}

void Player::addText(const sf::Text & text)
{
	m_text = text;
}


const sf::Text & Player::getText()
{
	return m_text;
}

bool Player::hasShape(const std::shared_ptr<Shape> &shape) const
{

	if (std::find(m_shapes.begin(), m_shapes.end(), shape) == m_shapes.end())
		return false;
	return true;
}

bool Player::nearbyToShapes(const std::vector<std::shared_ptr<Shape>> &shapes, const std::shared_ptr<Shape>& otherShape, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap) const
{
	for (auto &shape : shapes)
	{
		auto nearbyShapes = nearbyMap.find(shape);
		if (nearbyShapes == nearbyMap.end())
			continue; //will not reach this
		if (std::find(nearbyShapes->second.begin(), nearbyShapes->second.end(), otherShape) != nearbyShapes->second.end())
			return true;
	}

	return false;
}


void Player::play(const std::vector<std::shared_ptr<Shape>>& shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap)
{
	std::copy_if(shapes.begin(), shapes.end(), std::back_inserter(m_shapes), [&](const std::shared_ptr<Shape> &shape)
	{return (!hasShape(shape) && (shape->getUsedColor() == m_usedColor.first) && nearbyToShapes(m_shapes, shape, nearbyMap)); });
}


void Player::updateScore(const unsigned size)
{
	m_score = (double)m_shapes.size() / (double)size;
	m_text.setString(m_name + ": " + std::to_string(m_score));

}

const double Player::getScore() const
{
	return m_score;
}


void Player::clear()
{
	m_shapes.clear();
	m_score = 0;
}

void Player::draw(sf::RenderWindow & window)
{
	window.draw(m_text);
}



