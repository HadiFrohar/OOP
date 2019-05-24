#include "ShapesController.h"
#include <random>
#include "Settings.h"
#include <algorithm>
#include "Rectangle.h"
#include "Triangle.h"

ShapesController::ShapesController()
	:m_colorController(std::make_shared<ColorController>())
{
}

void ShapesController::createShapes()
{
	m_nearbyMap.clear();
	m_shapes.clear();

	std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>> shapesIndexes;
	unsigned numOfShapes = 0;
	for (int i = (int)(BOARD_SCALE * WINDOWSIZE / SHAPE_SIZE)-1; i >= 0; i--)
		for (int j = 0; j < BOARD_SCALE*WINDOWSIZE / SHAPE_SIZE; j++)
		{
			createShape({ (float)(1 - BOARD_SCALE) / 2 * WINDOWSIZE + j * SHAPE_SIZE
				,(float)(0.99 - BOARD_SCALE)*WINDOWSIZE + i * SHAPE_SIZE });
			std::list<std::shared_ptr<Shape>> shapesInIndex;
			while (numOfShapes < m_shapes.size())
			{
				shapesInIndex.push_front(m_shapes[numOfShapes]);
				numOfShapes++;
			}
			shapesIndexes[i].push_back(shapesInIndex);

		}
	createNearbyMap(shapesIndexes);

}

std::vector<std::shared_ptr<Shape>> &ShapesController::getShapes()
{
	return m_shapes;
}

std::vector<std::shared_ptr<Shape>>::iterator ShapesController::getShape(const sf::Vector2f & pos)
{	
	std::vector<std::shared_ptr<Shape>>::iterator it = std::find_if(m_shapes.begin(), m_shapes.end(),
		[&pos](const std::shared_ptr<Shape>& shape) { return shape->getBounds().contains(pos); });
	
	return it;
	
}

void ShapesController::createNearbyMap(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>> &shapesIndexes)
{

	for (int row = (int)shapesIndexes.size() - 1; row >= 0; row--)

		for (int col = 0; col < (int)shapesIndexes[row].size(); col++)
		{
			updateTopNearby(shapesIndexes, row, col);
			updateBottomNearby(shapesIndexes, row, col);
			updateLeftNearby(shapesIndexes[row], col);
			updateRightNearby(shapesIndexes[row], col);
		}
}

std::unordered_map<std::shared_ptr<Shape>, std::vector<std::shared_ptr<Shape>>>& ShapesController::getNearbyMap()
{
	return m_nearbyMap;
}

void ShapesController::draw(sf::RenderWindow & window)
{
	for (auto &shape : m_shapes)
		window.draw(*shape);
}

void ShapesController::createShape(const sf::Vector2f & pos)
{
	int i = rand() % 3;

	if (pos == DOWN_LEFT || pos == TOP_RIGHT)
		i = 0;

	if (i == 0)
		m_shapes.push_back(std::make_shared<Rectangle>(Rectangle(pos,m_colorController->getRandomColor())));
	else
	{
		m_shapes.push_back(std::make_shared<Triangle>(Triangle(pos, m_colorController->getRandomColor(), false)));
		m_shapes.push_back(std::make_shared<Triangle>(Triangle(pos, m_colorController->getRandomColor(), true)));

	}
}


std::shared_ptr<ColorController> & ShapesController::getColorController()
{
	return m_colorController;
}

void ShapesController::updateLeftNearby(std::vector<std::list<std::shared_ptr<Shape>>>& shapesRow, int col)
{
	auto it = shapesRow[col].begin();
	if (shapesRow[col].size() == 2)
		m_nearbyMap[*--shapesRow[col].end()].push_back(*it);
	if (col == 0)
		return;
	else
		m_nearbyMap[*it].push_back(*--shapesRow[col - 1].end());
}

void ShapesController::updateRightNearby(std::vector<std::list<std::shared_ptr<Shape>>>& shapesRow, int col)
{
	auto it = --shapesRow[col].end();
	if (shapesRow[col].size() == 2)
		m_nearbyMap[*shapesRow[col].begin()].push_back(*it);
	
	if (col == shapesRow.size() - 1)
		return;
	else
		m_nearbyMap[*it].push_back(*shapesRow[col + 1].begin());
}

void ShapesController::updateTopNearby(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>>& shapesIndexes, int row, int col)
{
	auto it = --shapesIndexes[row][col].end();
	if (shapesIndexes[col].size() == 2)
		m_nearbyMap[*shapesIndexes[row][col].begin()].push_back(*it);
	if (row == shapesIndexes.size() - 1)
		return;
	else
		m_nearbyMap[*it].push_back(*shapesIndexes[row+1][col].begin());
}

void ShapesController::updateBottomNearby(std::unordered_map<int, std::vector<std::list<std::shared_ptr<Shape>>>>& shapesIndexes, int row, int col)
{
	auto it = shapesIndexes[row][col].begin();
	if (shapesIndexes[col].size() == 2)
		m_nearbyMap[*--shapesIndexes[row][col].end()].push_back(*it);
	if (row == 0)
		return;
	else
		m_nearbyMap[*it].push_back(*shapesIndexes[row - 1][col].begin());
}
