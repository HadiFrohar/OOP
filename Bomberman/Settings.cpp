#include "Settings.h"

void getSettings(std::string firstLine, int &size, int &steps) {

	std::stringstream stream(firstLine);

	stream >> size;
	stream >> steps;
}

bool hasGuardRobot(std::vector<Guard> guards, Robot robot)
{
	for (size_t i = 0; i < guards.size(); i++)
		if (guards[i].getPosition().row == robot.getPosition().row && guards[i].getPosition().col == robot.getPosition().col)
			return true;

	return false;
}

void guardsMove(std::vector<std::string>map, std::vector<Guard> &guards, Robot robot)
{
	unsigned move;
	for (size_t i = 0; i < guards.size(); i++)
	{
		Position pos = guards[i].getPosition();
		srand((unsigned int)(time(NULL)+i));
		move = rand() % 4;
		switch (move)
		{
		case 0:
			if (robot.isUp(pos) && guards[i].canMove(map[pos.row - 1][pos.col]))
				guards[i].moveUp();
			else if (guards[i].canMove(map[pos.row + 1][pos.col]))
				guards[i].moveDown();
			break;

		case 1:
			if (!robot.isUp(pos) && guards[i].canMove(map[pos.row + 1][pos.col]))
				guards[i].moveDown();
			else if (guards[i].canMove(map[pos.row - 1][pos.col]))
				guards[i].moveUp();
			break;

		case 2:
			if (!robot.isRight(pos) && guards[i].canMove(map[pos.row][pos.col - 1]))
				guards[i].moveLeft();
			else if (guards[i].canMove(map[pos.row][pos.col + 1]))
				guards[i].moveRight();
			break;

		case 3:
			if (robot.isRight(pos) && guards[i].canMove(map[pos.row][pos.col + 1]))
				guards[i].moveRight();
			else if (guards[i].canMove(map[pos.row][pos.col - 1]))
				guards[i].moveLeft();
			break;


		}
	}
}

/*void clearGuards(std::vector<std::string>&map, std::vector<Guard> guards)
{
	for (size_t i = 0; i < guards.size(); i++)
	{
		Position pos = guards[i].getPosition();
		map[pos.row][pos.col] = ' ';
	}
}*/


void decreaseBombsTime(std::vector<Bomb> &bombs)
{
	for (size_t i = 0; i < bombs.size(); i++)
		bombs[i].decreaseTime();
}

void checkBombs(std::vector<Bomb> &bombs) {
	for (size_t i = 0; i<bombs.size(); i++)
		if (bombs[i].getTime() == -1)
			bombs.erase(bombs.begin());
}

bool hasBomb(std::vector<Bomb> bombs, Position pos)
{
	for (size_t i = 0; i < bombs.size(); i++)
		if (bombs[i].getPosition().row == pos.row && bombs[i].getPosition().col == pos.col)
			return true;
	return false;
}