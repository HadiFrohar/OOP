#include "Bullet.h"
#include "Util.h"
#include "Brick.h"
#include "Water.h"
#include "Tank.h"
#include "Bushes.h"
#include <typeinfo>


Bullet::Bullet(const sf::Vector2f & pos, int direction)
	: MovableObject(pos, sheetsController->bullet->getSheets(), sheetsController->bullet->getData()[direction]), m_direction(direction), m_destroyed(false), explosionId(0), m_speed(200.0f)
{
}


void Bullet::draw(sf::RenderWindow * window)
{

	updateBullet();
	Object::draw(window);
}


bool Bullet::isDestroyed() const
{
	return m_destroyed && m_time >= sf::milliseconds(100);
}

void Bullet::collide(Object * object)
{
	if (m_destroyed)
		return;
	else if (collision(this, object))
	{
		if(typeid(*object) != typeid(Bushes) && typeid(*object) != typeid(Water))
			destroy();
		if (m_friendly && dynamic_cast<Tank*>(object))
			return;

		object->collideWith(this);
	}
}

void Bullet::checkCollision(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, Tank *owner, vector<unique_ptr<Tank>> &tanks, vector<unique_ptr<Tank>>::iterator &it1, vector<unique_ptr<Tank>>::iterator &it2, Basement* basement, const sf::Time &dt)
{
	m_time += dt;
	if(m_destroyed)
		return;


	if (isOutsideGameBoard(this, gameBoard))
	{
		destroy();
		return;
	}
	collide(basement);

	for (auto it = tanks.begin(); it < tanks.end() && !m_destroyed; ++it)
	{
		m_friendly = true;
		if (it->get() != owner && (*it)->isAlive())
		{
			if (it >= it1 && it <= it2)
				m_friendly = false;
			collide(it->get());
		}

		(*it)->checkCollisionWithBullets(this);
		if (m_destroyed)
			return;
	}

	for (auto it = fixedObjects.begin(); it != fixedObjects.end(); )
	{
		collide(it->get());
		if (m_destroyed && typeid(*(it->get())) == typeid(Brick) && collision(this, it->get()))
			it = fixedObjects.erase(it);
		else
			++it;
	}
}

void Bullet::updateBullet()
{
	if (!m_destroyed)
	{
		if (m_direction == UP)
			m_sprite.move(0, -m_speed * m_time.asSeconds());
		else if (m_direction == DOWN)
			m_sprite.move(0, m_speed * m_time.asSeconds());
		else if (m_direction == LEFT)
			m_sprite.move(-m_speed * m_time.asSeconds(), 0);
		else if (m_direction == RIGHT)
			m_sprite.move(m_speed * m_time.asSeconds(), 0);

		m_time = sf::Time::Zero;
	}
	else
	{
		if (explosionId >= 3)
			return;
		
		m_sprite.setTextureRect(*sheetsController->explosion->getData()[explosionId]);
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		explosionId++;
		m_time = sf::Time::Zero;
	}
}

void Bullet::destroy()
{
	m_destroyed = true;
	m_sprite.setTexture(sheetsController->explosion->getSheets());
	m_time = sf::Time::Zero;
}


