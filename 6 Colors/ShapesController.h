#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <list>
#include "ColorController.h"
#include "Shape.h"
#include <memory>

class ShapesController
{
public:
	ShapesController();

	//creates shapes and nearby map(for every shape it has a vector of nearby shapes)
	void createShapes();

	//returns game shapes (rectangles, triangles)
	std::vector<std::shared_ptr<Shape>> &getShapes();

	//returns shape in a specific position
	std::vector<std::shared_ptr<Shape>>::iterator getShape(const sf::Vector2f &pos);

	//returns nearby map (for every shape it has a vector of nearby shapes)
	std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> &getNearbyMap();

	//draws game shapes
	void draw(sf::RenderWindow &window);

	//returns shared pointer of color controller object
	std::shared_ptr<ColorController> &getColorController();

private:

	//creates random shape in position, it either creates two triangles (that forms a rectangle, or one rectangle)
	void createShape(const sf::Vector2f &pos);

	//creates nearby map, it gets an table in the size of the maximum number of positions, and each
	//index contains the shapes in a specfic position (either 2 triangles or 1 rectangle)
	void createNearbyMap(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>> &shapesIndexes);
	
	//updates nearby shapes of an shape in the nearby map
	void updateLeftNearby(std::vector<std::list<std::shared_ptr<Shape>>> & shapesRow, int col);
	//updates nearby shapes of an shape in the nearby map
	void updateRightNearby(std::vector<std::list<std::shared_ptr<Shape>>> & shapesRow, int col);
	//updates nearby shapes of an shape in the nearby map
	void updateTopNearby(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>> &shapesIndexes, int row, int col);
	//updates nearby shapes of an shape in the nearby map
	void updateBottomNearby(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>> &shapesIndexes, int row, int col);

	//color controller object, it contains all the colors in game
	std::shared_ptr<ColorController> m_colorController;

	std::vector<std::shared_ptr<Shape>> m_shapes; //game shapes (rectangles, triangles)

	//nearby map, each shape has its nearby shapes
	std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>> m_nearbyMap;
};

