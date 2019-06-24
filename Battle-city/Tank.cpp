#include "Tank.h"
#include <typeinfo>
#include "Water.h"
#include "Brick.h"
#include "Stone.h"
#include "Basement.h"

Tank::Tank(const sf::Vector2f & pos, const sf::Texture & texture, vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>& intRects, int direction, int armor)
	: MovableObject(pos, texture, intRects[2].first), m_pos(pos), m_direction(direction), m_intRects(intRects), m_tankTexture(texture), m_destroyed(false), m_armor(armor), m_slowMovement(false), m_canMove(true)
{
	restart();
}

void Tank::draw(sf::RenderWindow * window)
{
	if (m_appearingEffect)
		if (m_lifeTime > sf::milliseconds(1000))
		{
			m_appearingEffect = false;
			resetSprite();
		}
		else
			appearEffect();

		Object::draw(window);

		for (auto &bullet : m_bullets)
			bullet->draw(window);
		
}

void Tank::move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape * gameBoard, std::vector<unique_ptr<Tank>>& tanks, Basement * basement, const sf::Time & dt)
{
	m_sprite.move(m_movement);
	checkMovement(fixedObjects, gameBoard, tanks, basement);
	if (!m_canMove)
	{
		m_sprite.move(-m_movement);
		m_canMove = true;
	}
	else if(m_slowMovement)
	{
		m_slowMovement = false;
		m_sprite.move(-(float)0.5*m_movement.x, -(float)0.5*m_movement.y);

	}

	m_movement = { 0,0 };
}

void Tank::destroy()
{

	m_destroyed = true;
	m_effectId = 0;
	m_lifeTime = sf::Time::Zero;
	m_sprite.setTexture(sheetsController->explosion->getSheets());
}

void Tank::restart()
{
	m_bullets.clear();
	m_sprite.setPosition(m_pos);
	m_appearingEffect = true;
	m_effectId = 0;
	m_sprite.setTexture(sheetsController->tankEffects->getSheets());
	m_lifeTime = sf::Time::Zero;
}

void Tank::collide(Object * object)
{
	object->collideWith(this);
}

void Tank::collideWith(Bullet * bullet)
{
		damage();
}

void Tank::collideWith(Wall * wall)
{
	m_canMove = false;
}

void Tank::collideWith(Water * water)
{
	m_slowMovement = true;
}

void Tank::collideWith(Basement * basement)
{
	m_canMove = false;
}

void Tank::damage()
{
	if (m_appearingEffect)
		return;
	m_armor--;
	if (m_armor <= 0)
		destroy();
}

void Tank::slowMovement()
{
	m_slowMovement = true;
}

bool Tank::isAlive()
{
	return !m_appearingEffect && !m_destroyed;
}

bool Tank::isBoomed()
{
	return m_destroyed && m_lifeTime > sf::milliseconds(500);
}

const sf::Vector2f & Tank::getTankPos() const
{
	return m_pos;
}

void Tank::checkCollisionWithBullets(Bullet * bullet)
{
	for (auto it = m_bullets.begin(); it != m_bullets.end(); ++it)
		if (it->get() != bullet && collision(it->get(), bullet))
		{
			(*it)->collide(bullet);
			bullet->collide(it->get());
		}
}

void Tank::newBullet()
{

	sf::Vector2f bulletPos = m_sprite.getPosition();

	switch (m_direction)
	{
	case UP:
		bulletPos.x += m_sprite.getGlobalBounds().width / 2 - 4;
		break;
	case DOWN:
		bulletPos.x += m_sprite.getGlobalBounds().width / 2 - 4;
		bulletPos.y += m_sprite.getGlobalBounds().height;
		break;
	case LEFT: 
		bulletPos.x -= 8;
		bulletPos.y += m_sprite.getGlobalBounds().height / 2 - 4;
		break;
	case RIGHT:
		bulletPos.x += m_sprite.getGlobalBounds().width;
		bulletPos.y += m_sprite.getGlobalBounds().height / 2 - 4;
		break;
	default: return; break;
	}
	
	m_bullets.emplace_back(std::make_unique<Bullet>(bulletPos, m_direction));

	m_bulletPassedTime = sf::Time::Zero;
}

void Tank::updateAnimation(int direction)
{
	if (m_direction != direction)
	{
		m_direction = direction;
		m_sprite.setTextureRect(*m_intRects[m_direction].first);
	}

	if (m_animationPassedTime < m_animationTime)
		return;

	if (m_sprite.getTextureRect() == *m_intRects[m_direction].first)
		m_sprite.setTextureRect(*m_intRects[m_direction].second);
	else
		m_sprite.setTextureRect(*m_intRects[m_direction].first);

	m_animationPassedTime = sf::Time::Zero;
}

sf::Vector2f Tank::leftMovement(const float &dt)
{

	sf::Vector2f movement = { -m_speed * dt, (float)(m_intRects[m_direction].first->height - m_intRects[LEFT].first->height) };
	updateAnimation(LEFT);
	return movement;
}

sf::Vector2f Tank::rightMovement(const float &dt)
{

	sf::Vector2f movement = { m_speed * dt, (float)(m_intRects[m_direction].first->height - m_intRects[RIGHT].first->height) };
	updateAnimation(RIGHT);
	return movement;
}

sf::Vector2f Tank::upMovement(const float &dt)
{
	
	sf::Vector2f movement = { (float)(m_intRects[m_direction].first->width - m_intRects[UP].first->width), -m_speed * dt };
	updateAnimation(UP);
	return movement;
}

sf::Vector2f Tank::downMovement(const float &dt)
{
	
	sf::Vector2f movement = { (float)(m_intRects[m_direction].first->width - m_intRects[DOWN].first->width), m_speed * dt };
	updateAnimation(DOWN);
	return movement;
}


void Tank::checkMovement(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement)
{
	if (isOutsideGameBoard(this, gameBoard))
	{
		m_canMove = false;
	}

	for (auto it = fixedObjects.begin(); it != fixedObjects.end(); ++it)
		(*it)->collide(this);

	basement->collide(this);

}

void Tank::checkBullets(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, vector<unique_ptr<Tank>> &tanks, std::vector<unique_ptr<Tank>>::iterator &it1, std::vector<unique_ptr<Tank>>::iterator &it2, Basement* basement, const sf::Time &dt)
{
	for (auto it = m_bullets.begin(); it != m_bullets.end();)
	{
		if ((*it)->isDestroyed())
			it = m_bullets.erase(it);
		else
		{
			(*it)->checkCollision(fixedObjects, gameBoard, this, tanks, it1, it2, basement, dt);
			++it;
		}
	}

}

void Tank::resetSprite()
{
	m_sprite.setTexture(m_tankTexture);
	m_sprite.setTextureRect(*m_intRects[2].first);
	m_sprite.setOrigin(0, 0);
}

void Tank::appearEffect()
{
	if (m_animationPassedTime < sf::milliseconds(100))
		return;

	m_sprite.setTextureRect(*sheetsController->tankEffects->getData()[m_effectId%4]);
	m_effectId++;
	m_animationPassedTime = sf::Time::Zero;
}

void Tank::boomEffect()
{
	if (m_animationPassedTime < sf::milliseconds(100) || m_effectId >= 5)
		return;
	m_sprite.setTextureRect(*sheetsController->explosion->getData()[m_effectId]);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_effectId++;
	m_animationPassedTime = sf::Time::Zero;
}

void Tank::updateTime(const sf::Time & dt)
{
	m_lifeTime += dt;
	m_animationPassedTime += dt;
	m_bulletPassedTime += dt;

}

