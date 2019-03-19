#include "Utilities.h"

std::vector<std::string> getMap(std::fstream &file, int &size, int &steps)
{

	std::vector<std::string> map;
	std::string inputString;
	while (getline(file, inputString) && inputString.empty());


	std::stringstream stream(inputString);

	stream >> size >> steps;
	for (int i = 0; i < size; i++)
	{
		getline(file, inputString);
		map.push_back(inputString);
	}

	return map;
}

std::vector<std::string> createEmptyMap(int size)
{
	std::vector<std::string> map;

	for (int i = 0; i < size; i++)
	{
		std::string line(size, WHITESPACE);
		for (int j = 0; j < size; j++)
			if (i == 0 || i == size - 1)
				line[j] = WALL;
			else if (j == 0 || j == size - 1)
				line[j] = WALL;
		map.push_back(line);
	}

	return map;

}

void updateMapInFile(std::vector<std::string> map, int size, int steps)
{
	std::ofstream file(MAPPATH, std::ios::out | std::ios::trunc);
	file << size << ' ' << steps << '\n';
	for (size_t i = 0; i < map.size(); i++)
	{
		file << map[i];
		if (i != map.size() - 1)
			file << NEWLINE;
	}
	file.close();

}

sf::RectangleShape createOverShape(const sf::Vector2f& pos, std::string imgPath)
{
	sf::Texture texture;
	texture.loadFromFile(imgPath);

	sf::RectangleShape type({ DEFAULT_SIZE, DEFAULT_SIZE });


	type.setPosition(pos);
	type.setTexture(&texture);
	type.setOutlineColor(sf::Color::Red);
	type.setOutlineThickness(2);
	return type;
}


bool hasPoint(std::vector<Object> objects, const sf::Vector2f & pos)
{
	for (size_t i = 0; i < objects.size(); i++)
		if (objects[i].getPosition() == pos)
			return true;
	return false;
}

void writeOnMap(std::vector<std::string>& map, std::vector<Object> objects)
{
	int row,
		col;
	for (size_t i = 0; i < objects.size(); i++)
	{
		row = (int) (objects[i].getPosition().y- GAME_Y_POS) / DEFAULT_SIZE;
		col = (int) objects[i].getPosition().x / DEFAULT_SIZE;
		map[row][col] = objects[i].getType();
	}
}

void writeOnMapChar(std::vector<std::string>& map, const sf::Vector2f & pos, char c)
{
	int row,
		col;
	row = (int)(pos.y - GAME_Y_POS) / DEFAULT_SIZE;
	col = (int)pos.x / DEFAULT_SIZE;
	map[row][col] = c;
}