#include "Enemy.h"



Enemy::Enemy(const sf::Vector2f & pos, const sf::Texture & texture, vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>& intRects, int life)
	:Tank(pos, texture, intRects, DOWN, life)
{
	m_animationTime = sf::milliseconds(70);
	m_tankPower = 1500;
	m_speed = ENEMY_SPEED;
	restart();
}

void Enemy::move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape * gameBoard, std::vector<unique_ptr<Tank>>& tanks, Basement * basement, const sf::Time &dt)
{
	updateTime(dt);
	auto it1 = tanks.begin();
	auto it2 = tanks.begin();
	checkBullets(fixedObjects, gameBoard, tanks, it1, it2, basement, dt);

	if (m_appearingEffect || m_destroyed)
		return;

	if (m_bulletPassedTime > m_bulletTime)
		updateBullets();
	if (m_pMovementTime > m_movementTime)
	{
		resetMovementTime();
		updateMovement(tanks[0].get(), basement);
	}

	m_movement = getMovement(dt);

	Tank::move(fixedObjects, gameBoard, tanks, basement, dt);
	
}

void Enemy::draw(sf::RenderWindow * window)
{
	if (m_destroyed)
		boomEffect();
		
	Tank::draw(window);
}


void Enemy::updateTime(const sf::Time & dt)
{
	Tank::updateTime(dt);
	m_pTargetTime += dt;
	m_pMovementTime += dt;
}


void Enemy::updateTarget(Tank * player, Basement * basement)
{
	m_targetTime = sf::milliseconds(rand() % 1000 + 1000);
	m_pTargetTime = sf::Time::Zero;

	if (distance(player) < distance(basement))
		m_target = player;
	else
		m_target = basement;
}

float Enemy::distance(const Object * otherObject)
{
	sf::Vector2f thisCenter = getPosition();
	sf::Vector2f otherCenter = otherObject->getPosition();
	return sqrt(pow(thisCenter.x - otherCenter.x, 2) + pow(thisCenter.y - otherCenter.y, 2));
}

sf::Vector2f Enemy::getMovement(const sf::Time &dt)
{
	switch (m_direction)
	{
	case UP: return upMovement(dt.asSeconds()); break;
	case DOWN: return downMovement(dt.asSeconds()); break;
	case RIGHT: return rightMovement(dt.asSeconds()); break;
	case LEFT: return leftMovement(dt.asSeconds()); break;
	default: return { 0,0 }; break;
	}

}

void Enemy::updateMovement(Tank * player, Basement * basement)
{
	int r = rand() % 5;
	if (r == 2)
		m_direction = rand() % 4;
	else
		updateDirection();
}

void Enemy::resetMovementTime()
{
	m_movementTime = sf::milliseconds(rand() % 500 + 200);
	m_pMovementTime = sf::Time::Zero;
}

void Enemy::updateDirection()
{

	if ((rand() % 2) == 0)//y
	{
		if (m_sprite.getPosition().y <= m_target->getPosition().y && abs(m_sprite.getPosition().y - m_target->getPosition().y) > getGlobalBounds().height)
			m_direction = DOWN;
		else if (m_sprite.getPosition().y > m_target->getPosition().y && abs(m_sprite.getPosition().y - m_target->getPosition().y) > getGlobalBounds().height)
			m_direction = UP;
		else if (m_sprite.getPosition().x <= m_target->getPosition().x && abs(m_sprite.getPosition().x - m_target->getPosition().x) > getGlobalBounds().width)
			m_direction = RIGHT;
		else if (m_sprite.getPosition().x > m_target->getPosition().x && abs(m_sprite.getPosition().x - m_target->getPosition().x) > getGlobalBounds().width)
			m_direction = LEFT;
		else
			m_direction = NOMOVE;
	}

	else
	{
		if (m_sprite.getPosition().x < m_target->getPosition().x && abs(m_sprite.getPosition().x - m_target->getPosition().x) > getGlobalBounds().width)
			m_direction = RIGHT;
		else if (m_sprite.getPosition().x >= m_target->getPosition().x && abs(m_sprite.getPosition().x - m_target->getPosition().x) > getGlobalBounds().width)
			m_direction = LEFT;
		else if (m_sprite.getPosition().y < m_target->getPosition().y && abs(m_sprite.getPosition().y - m_target->getPosition().y) > getGlobalBounds().height)
			m_direction = DOWN;
		else if (m_sprite.getPosition().y >= m_target->getPosition().y && abs(m_sprite.getPosition().y - m_target->getPosition().y) > getGlobalBounds().height)
			m_direction = UP;
		else
			m_direction = NOMOVE;
	}

}


void Enemy::updateBullets()
{
	newBullet();
	m_bulletPassedTime = sf::Time::Zero;
	m_bulletTime = sf::milliseconds(rand() % 500 + m_tankPower);
}
