#pragma once
#include "Player.h"
#include "ColorController.h"


class Computer : public Player
{
public:
	Computer();
	//returns for each color how many shapes the computer can get if it played with color
	std::vector<std::pair<int, int>> nearbyColorsCount(const std::vector<std::shared_ptr<Shape>> &shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap, std::shared_ptr<ColorController> &controller);

private:
	//returns for a specifc color all the nearby shapes (that the computer can get if it played with color)
	std::vector<std::shared_ptr<Shape>> getNearbyOfColor(const std::vector<std::shared_ptr<Shape>> &shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap, const sf::Color &color);

};

