#include "Computer.h"



Computer::Computer()
	:Player("Computer")
{
}


std::vector<std::pair<int,int>> Computer::nearbyColorsCount(const std::vector<std::shared_ptr<Shape>> &shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap, std::shared_ptr<ColorController> &controller)
{
	std::vector<std::pair<int, int>> colorsList;

	for (int i = 0; i < controller->getNumOfcolors(); i++)
		colorsList.push_back(std::make_pair(i, (int)getNearbyOfColor(shapes, nearbyMap, controller->getColor(i).first).size()));

	std::sort(colorsList.begin(), colorsList.end(), [&colorsList]
	(const std::pair<int, int> &p1, std::pair<int, int> &p2) {return p2.second<p1.second; });
	
	return colorsList;
		
}

std::vector<std::shared_ptr<Shape>> Computer::getNearbyOfColor(const std::vector<std::shared_ptr<Shape>>& shapes, const std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &nearbyMap, const sf::Color &color)
{
	std::vector<std::shared_ptr<Shape>> nearbyShapes;

	std::copy_if(shapes.rbegin(), shapes.rend(), std::back_inserter(nearbyShapes), [&](const std::shared_ptr<Shape> &shape)
	{return (!hasShape(shape) && (shape->getUsedColor() == color) && (nearbyToShapes(m_shapes, shape, nearbyMap) || nearbyToShapes(nearbyShapes, shape, nearbyMap))); });
	
	return nearbyShapes;
}
