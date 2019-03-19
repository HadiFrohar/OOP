#include "Robot.h"

Robot::Robot()
	:MoveableObject(), m_life(STARTLIFE), m_score(EMPTY)
{
	//GUARD_X =0, GUARD_Y=100
	setType(ROBOT, sf::IntRect(FIRST, FIRST, OBJECTIMGSIZE, OBJECTIMGSIZE));
	clear();
	m_movementTime = sf::milliseconds(50);
	m_animationTime = sf::milliseconds(80);
}

void Robot::clear()
{
	setPoisiton({ 0,0 });
	m_inDamage = false;
}

void Robot::resetScore()
{
	m_score = 0;
}

void Robot::setStartLife()
{
	m_life = STARTLIFE;
}

void Robot::move(std::vector<std::unique_ptr<Object>> &staticObjects, std::vector<Bomb> &bombs, sf::View &view, int mapSize)
{

	if (m_inDamage && m_damageClock.getElapsedTime().asSeconds() < PROTECTIONTIME)
		if (m_damageClock.getElapsedTime().asMilliseconds() % 1000 < 250)
			setSize(0.75f);
		else if (m_damageClock.getElapsedTime().asMilliseconds() % 1000 > 500 &&
			m_damageClock.getElapsedTime().asMilliseconds() % 1000 < 750)
			setSize(0.8f);
		else
			setSize(0.9f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		placeBomb(bombs);

	updateAnimation();

	if (m_movementClock.getElapsedTime() < m_movementTime)
		return;

	m_movementClock.restart();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_movement != LEFT)
		{
			m_shapeType = 0;
			m_movement = LEFT;
		}
		moveLeft();
		if (!canMove(staticObjects))
			moveRight();
		else
		{
			if (mapSize > WINDOWSIZE)
				if (view.getCenter().x > WINDOWSIZE / 2 && getPosition().x < mapSize - WINDOWSIZE / 2)
					view.move(-SPEED, 0);
			return;
		}


	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		if (m_movement != RIGHT)
		{
			m_shapeType = 0;
			m_movement = RIGHT;
		}

		moveRight();
		if (!canMove(staticObjects))
			moveLeft();
		else
		{
			if (mapSize > WINDOWSIZE)
				if (getPosition().x > WINDOWSIZE / 2 && getPosition().x < mapSize - WINDOWSIZE / 2)
					view.move(SPEED, 0);
			return;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_movement != UP)
		{
			m_shapeType = 0;
			m_movement = UP;
		}

		moveUp();
		if (!canMove(staticObjects))
			moveDown();
		else
		{
			if (mapSize > WINDOWSIZE)
				if (view.getCenter().y > WINDOWSIZE / 2 && getPosition().y < mapSize - WINDOWSIZE / 2)
					view.move(0, -SPEED);
			return;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_movement != DOWN)
		{
			m_shapeType = 0;
			m_movement = DOWN;
		}

		moveDown();
		if (!canMove(staticObjects))
			moveUp();
		else
		{
			if (mapSize > WINDOWSIZE)
				if (getPosition().y > WINDOWSIZE / 2 && getPosition().y < mapSize - WINDOWSIZE / 2)
					view.move(0, SPEED);
			return;
		}
	}

	m_shapeType = 0;

	setImgPos(sf::IntRect(0, OBJECTIMGSIZE*m_movement, OBJECTIMGSIZE, OBJECTIMGSIZE));

}

bool Robot::isUp(sf::Vector2f &pos)
{
	if (getPosition().y < pos.y)
		return true;
	return false;
}

bool Robot::isRight(sf::Vector2f &pos)
{
	if (getPosition().x > pos.x)
		return true;
	return false;
}

void Robot::damage()
{
	if (!m_inDamage)
		m_damageClock.restart();


	if (!m_inDamage)
	{
		m_life--;
		m_inDamage = true;
	}
	else if (m_damageClock.getElapsedTime().asSeconds() >= PROTECTIONTIME)
	{
		m_inDamage = false;
		damage();
	}
}


int Robot::getLife()
{
	return m_life;
}

bool Robot::isInProtection()
{
	return m_inDamage;
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
	sf::RectangleShape doorRect({ 1, 1 });
	doorRect.setPosition({ door.getPosition().x + OBJECTSIZE / 2, door.getPosition().y + OBJECTSIZE / 2 });

	if (getShape().getGlobalBounds().intersects(doorRect.getGlobalBounds()))
		return true;

	return false;
}

bool Robot::isAlive()
{
	if (m_life > 0)
		return true;
	else
		return false;
}

void Robot::setBombs(int bombs)
{
	m_bombs = bombs;
}

int Robot::getBombs()
{
	return m_bombs;
}


void Robot::placeBomb(std::vector<Bomb> &bombs)
{
	bool hasBomb = false;
	for (size_t i = 0; i < bombs.size(); i++)
		if (collision(bombs[i].getShape()))
			hasBomb = true;
	if (m_bombs > 0 && !hasBomb)
	{
		bombs.push_back(Bomb(getPosition(), getSheets()));
		m_bombs--;
	}
}

void Robot::moveLeft()
{
	getPositionAsRef().x -= SPEED;
}

void Robot::moveRight()
{
	getPositionAsRef().x += SPEED;
}

void Robot::moveDown()
{
	getPositionAsRef().y += SPEED;
}

void Robot::moveUp()
{
	getPositionAsRef().y -= SPEED;
}

void Robot::updateAnimation()
{
	if (m_animationClock.getElapsedTime() > m_movementTime)
	{
		m_shapeType++;
		if (m_shapeType == 3)
			m_shapeType = 0;
		m_animationClock.restart();
	}
	setImgPos(sf::IntRect(OBJECTIMGSIZE*m_shapeType, SECOND*m_movement, OBJECTIMGSIZE, OBJECTIMGSIZE));
}
