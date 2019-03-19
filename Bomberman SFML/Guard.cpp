#include "Guard.h"

Guard::Guard(const sf::Vector2f & pos, const sf::Texture& sheets)
	:MoveableObject(pos, sheets)

{
	//GUARD_X =0, GUARD_Y=100
	setType(GUARD, sf::IntRect(FIRST, FIFTH, OBJECTIMGSIZE, OBJECTIMGSIZE));
	m_movementTime = sf::milliseconds(40);
	m_animationTime = sf::milliseconds(80);

}


void Guard::move(std::vector<std::unique_ptr<Object>> &staticObjects, Robot &robot, Door &door, int i)
{
	updateAnimation();

	if (m_movementClock.getElapsedTime() < m_movementTime)
		return;

	m_movementClock.restart();

	noMove = false;

	unsigned move;
	srand((unsigned int)(time(NULL)+i));
	move = rand() % 2;
	switch (move)
	{
	case 0:
		if (robot.isUp(getPositionAsRef()))
		{
			moveUp();
			if (!canMove(staticObjects))
			{
				moveDown();
				noMove = true;
			}
		}
		else
		{
			moveDown();
			if (!canMove(staticObjects) || collision(door.getShape()))
			{
				moveUp();
				noMove = true;
			}
		}
		break;
	case 1:
		if (robot.isRight(getPositionAsRef()))
		{
			moveRight();
			if (!canMove(staticObjects) || collision(door.getShape()))
			{
				moveLeft();
				noMove = true;
			}
		}
		else
		{
			moveLeft();
			if (!canMove(staticObjects) || collision(door.getShape()))
			{
				noMove = true;
				moveRight();
			}
		}
		break;
	default:
		noMove = true;
		break;
	}

}

void Guard::isInRobotRange(Robot & robot)
{
	if (collision(robot.getShape()))
		robot.damage();
}

void Guard::moveLeft()
{
	if (m_movement != LEFT)
	{
		m_shapeType = 0;
		m_movement = LEFT;
	}


	getPositionAsRef().x -= SPEED;
}

void Guard::moveRight()
{
	if (m_movement != RIGHT)
	{
		m_shapeType = 0;
		m_movement = RIGHT;
	}


	getPositionAsRef().x += SPEED;
}

void Guard::moveDown()
{
	if (m_movement != DOWN)
	{
		m_shapeType = 0;
		m_movement = DOWN;
	}

	getPositionAsRef().y += SPEED;
}

void Guard::moveUp()
{
	if (m_movement != UP)
	{
		m_shapeType = 0;
		m_movement = UP;
	}

	getPositionAsRef().y -= SPEED;
}

void Guard::updateAnimation()
{
	if (m_animationClock.getElapsedTime() > m_movementTime)
	{
		if(!noMove)
			m_shapeType++;
		if (m_shapeType == 2)
			m_shapeType = 0;
		m_animationClock.restart();
	}
	if(!noMove)
		setImgPos(sf::IntRect(OBJECTIMGSIZE*m_shapeType, FIFTH + OBJECTIMGSIZE * m_movement, OBJECTIMGSIZE, OBJECTIMGSIZE));
	else
		setImgPos(sf::IntRect(0, FIFTH + OBJECTIMGSIZE * m_movement, OBJECTIMGSIZE, OBJECTIMGSIZE));

}
