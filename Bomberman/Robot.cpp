#include "Robot.h"
#include "Settings.h"

Robot::Robot()
{
	m_life = START_LIFE;
	m_score = EMPTY;
}

void Robot::setPosition(short row, short col) {
	m_position = { row, col };
}

Position Robot::getPosition()
{
	return m_position;
}

bool Robot::isUp(Position pos)
{
	if (m_position.row < pos.row)
		return true;
	return false;
}

bool Robot::isRight(Position pos)
{
	if (m_position.col > pos.col)
		return true;
	return false;
}

void Robot::DecreaseLife()
{
	m_life--;
}


int Robot::getLife()
{
	return m_life;
}

bool Robot::canMove(char c)
{
	if (c == WALL || c == ROCK)
		return false;
	return true;
}

bool Robot::moveRobot(std::vector<std::string> map, std::vector<Bomb> &bombs)
{
	switch (Keyboard::getch())
	{
	case 0:
	case SPECIAL_KEY:
		switch (Keyboard::getch())
		{
		case KB_UP:
			if(!canMove(map[m_position.row-1][m_position.col]))
				return (moveRobot(map, bombs));
				m_position.row--;
			break;
		case KB_DOWN:
			if (!canMove(map[m_position.row + 1][m_position.col]))
				return (moveRobot(map, bombs));
			m_position.row++;
			break;
		case KB_LEFT:
			if (!canMove(map[m_position.row][m_position.col-1]))
				return (moveRobot(map, bombs));
			m_position.col--;
			break;
		case KB_RIGHT:
			if (!canMove(map[m_position.row][m_position.col+1]))
				return (moveRobot(map, bombs));
			m_position.col++;
			break;
		}
		break;
	case KB_SPACE:
		return false;
		break;
	default:
		return	(moveRobot(map, bombs));
		break;
	case KB_SMALLB:
		if (hasBomb(bombs, m_position))
			return (moveRobot(map, bombs));

			Bomb bomb(m_position);
			//bomb.setPosition(m_position.row, m_position.col);
			//bomb.setTime();
			bombs.push_back(bomb);
			return false;
		break;
	}

	return true;
}


bool Robot::onBomb(std::vector<Bomb> bombs)
{
	for (size_t i = 0; i < bombs.size(); i++)
		if (m_position.row == bombs[i].getPosition().row &&
			m_position.col == bombs[i].getPosition().col)
			return true;
	return false;
}

bool Robot::bombDamage(Bomb bomb)
{
	if (bomb.isInRadius(m_position) && bomb.getTime() == 0)
			return true;
	return false;
}


int Robot::getScore()
{
	return m_score;
}

void Robot::addScore(int score)
{
	m_score += score;
}

bool Robot::win(Door door)
{
	if (door.getPosition().row == m_position.row && door.getPosition().col == m_position.col)
		return true;
	return false;
}
