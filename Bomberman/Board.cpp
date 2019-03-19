#include "Board.h"


Board::Board()
{
	clear();
}
void Board::clear()
{
	m_map.clear();
	m_guards.clear();
	m_rocks.clear();
	m_bombs.clear();
}


void Board::setRobot(Robot robot) {
	m_robot = robot;
}

void Board::setSettings(std::vector<std::string> map, int size, int steps)
{
	m_map = map;
	m_mapSize = size;
	m_steps = steps;
}

int Board::getSteps()
{
	return m_steps;
}


/*void Board::setMap(std::vector<std::string> map)
{
	m_map = map;
}

void Board::setSize(int size)
{
	m_mapSize = size;
}

void Board::setSteps(int steps)
{
	m_steps = steps;
}
*/



void Board::readMap()
{

	for (size_t row = 0; row < m_map.size(); row++)
	{
		for (size_t col = 0; col < m_map.size(); col++)
		{
			if (m_map[row][col] == ROBOT)
			{
				m_map[row][col] = WHITESPACE;
				m_robot.setPosition((short)row, (short)col);
			}

			else if (m_map[row][col] == GUARD)
			{
				m_map[row][col] = WHITESPACE;
				Guard guard;
				guard.setPosition((short)row, (short)col);
				m_guards.push_back(guard);
			}

			else if (m_map[row][col] == DOOR)
			{
				m_door.setPosition((short)row, (short)col);
				m_map[row][col] = ROCK;
				Rock rock(m_door.getPosition());
				m_rocks.push_back(rock);
			}

			else if (m_map[row][col] == ROCK)
			{
				Rock rock({ (short)row, (short)col });
				m_rocks.push_back(rock);
			}
		}
	}

	m_guardsSize = m_guards.size();

//	clearGuards(m_map, m_guards);

}

bool Board::finishLevel()
{
	readMap();
	m_levelScore = 0;

	while (true)
	{
		moveCursor({ 0,0 });
		for (size_t i = 0; i < m_map.size(); ++i)
			std::cout << m_map[i]<<'\n';

		for (size_t i = 0; i < m_bombs.size(); i++)
		{
			moveCursor(m_bombs[i].getPosition());
			if (m_bombs[i].getTime() == 0)
			{
				std::cout << DESTROYED;
				if (m_bombs[i].getPosition().row > 1)
				{
					moveCursor({ m_bombs[i].getPosition().row - 1, m_bombs[i].getPosition().col });
					std::cout << DESTROYED;
				}
				if (m_bombs[i].getPosition().row < m_mapSize - 2)
				{
					moveCursor({ m_bombs[i].getPosition().row + 1, m_bombs[i].getPosition().col });
					std::cout << DESTROYED;
				}
				if (m_bombs[i].getPosition().col > 1)
				{
					moveCursor({ m_bombs[i].getPosition().row, m_bombs[i].getPosition().col - 1 });
					std::cout << DESTROYED;
				}
				if (m_bombs[i].getPosition().col < m_mapSize - 2)
				{
					moveCursor({ m_bombs[i].getPosition().row, m_bombs[i].getPosition().col + 1 });
					std::cout << DESTROYED;
				}
			}
			else
			{
				moveCursor(m_bombs[i].getPosition());
				std::cout << m_bombs[i].getTime();
			}
		}

		for (size_t i = 0; i < m_guards.size(); i++)
		{
			moveCursor(m_guards[i].getPosition());
			std::cout << GUARD;
		}

		moveCursor(m_robot.getPosition());
		if(!m_robot.onBomb(m_bombs))
			std::cout << ROBOT;
		else
			std::cout << ROBOT_ON_BOMB;

		if (hasGuardRobot(m_guards, m_robot))
			m_robot.DecreaseLife();

		for(size_t i=0; i< m_guards.size(); i++)
			if (m_guards[i].onBomb(m_bombs))
			{
				m_guards.erase(m_guards.begin() + i);
				killedGuard();
			}

		for (size_t i = 0; i < m_rocks.size(); i++)
		{
			if (m_rocks[i].inBombRadius(m_bombs))
			{
				if (m_rocks[i].getPosition().row == m_door.getPosition().row &&
					m_rocks[i].getPosition().col == m_door.getPosition().col)
					m_map[m_door.getPosition().row][m_door.getPosition().col] = DOOR;
				else
					m_map[m_rocks[i].getPosition().row][m_rocks[i].getPosition().col] = WHITESPACE;

				m_rocks.erase(m_rocks.begin()+i);
			}
		}

		if (m_robot.getLife() == 0 || m_steps == 0)
			return false;

		if (m_robot.moveRobot(m_map, m_bombs))
			m_steps--;

		if (hasGuardRobot(m_guards, m_robot))
			m_robot.DecreaseLife();

		guardsMove(m_map, m_guards, m_robot);

		decreaseBombsTime(m_bombs);
		for(size_t i=0; i<m_bombs.size(); i++)
			if (m_robot.bombDamage(m_bombs[i]))
				m_robot.DecreaseLife();

		checkBombs(m_bombs);
		moveCursor({ (short)m_mapSize, 0 });
		if (m_robot.win(m_door))
		{
			finishedLevel();
			m_robot.addScore(m_levelScore);
			std::printf("Life: %d, Steps: %d, Score: %d", m_robot.getLife(), m_steps, m_robot.getScore());
			return true;
		}
		
		std::printf("Life: %d, Steps: %d, Score: %d", m_robot.getLife(), m_steps, m_robot.getScore()+m_levelScore);

	}

	return true;

}

void Board::killedGuard()
{
	m_levelScore += 5 * m_guardsSize;
}

void Board::finishedLevel()
{
	m_levelScore += 20 * m_guardsSize;
}


std::vector<Bomb> Board::getBombs()
{
	return m_bombs;
}

void Board::addBomb(Bomb bomb)
{
	m_bombs.push_back(bomb);
}

void Board::removeBomb(size_t i)
{	
	m_bombs.erase(m_bombs.begin() + i);
}

Robot Board::getRobot()
{
	return m_robot;
}
