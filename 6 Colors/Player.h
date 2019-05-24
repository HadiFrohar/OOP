#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include <unordered_map>
#include <string>
#include "Settings.h"
#include <memory>
#include "Shape.h"

class Player
{
public:
	Player(std::string name);
	virtual ~Player() = 0 {}
	void addShape(std::shared_ptr<Shape> &shape); // adds shape to player shapes
	void updateColor(const std::pair<sf::Color, sf::Color> & color); //update color of player shapes
	void switchColor(); //switchs color of player shapes (in case animation is needed)
	const std::pair<sf::Color, sf::Color> &getUsedColor() const; //returns used color of player
	void addText(const sf::Text &text); //adds score text
	const sf::Text &getText(); //returns score text
	
	void play(const std::vector<std::shared_ptr<Shape>> &shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap);

	void updateScore(const unsigned size); //updates player score. shapes_size/size
	const double getScore() const; //returns player score


	void clear(); //clears player (score = 0, shapes = empty)
	void draw(sf::RenderWindow & window); //draws player score



protected:
	//checks if player has an specfic shape (the shape ptr is also in player shapes vector)
	bool hasShape(const std::shared_ptr<Shape> &shape) const;
	//checks if an specfic shape is nearby to player (for every shape of player, it checks if it is in the nearby shapes of shape in nearby map)
	bool nearbyToShapes(const std::vector<std::shared_ptr<Shape>> &shapes, const std::shared_ptr<Shape> & otherShape, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap) const;

	//player shapes
	std::vector<std::shared_ptr<Shape>> m_shapes;
	std::pair<sf::Color, sf::Color> m_usedColor; //pair for animation

private:
	sf::Text m_text; //player score text
	std::string m_name; //player name
	double m_score; //player score

};

