#include "Player.h"




Player::Player(const sf::Vector2f & pos)
	:Tank(pos, sheetsController->playerTank->getSheets(), sheetsController->playerTank->getData()[0], UP, 1)
{
}

void Player::move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement, const sf::Time &dt)
{
	updateTime(dt);

	auto it1 = ++tanks.begin();
	auto it2 = --tanks.end();
	checkBullets(fixedObjects, gameBoard, tanks, it1, it2, basement, dt);
	if (m_appearingEffect || m_destroyed)
		return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		if (m_bulletPassedTime > m_bulletTime)
			newBullet();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_movement = leftMovement(dt.asSeconds());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_movement = rightMovement(dt.asSeconds());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_movement = downMovement(dt.asSeconds());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_movement = upMovement(dt.asSeconds());

	Tank::move(fixedObjects, gameBoard, tanks, basement, dt);

}

void Player::draw(sf::RenderWindow * window)
{
	if (m_destroyed)
		if (isBoomed())
		{
			m_destroyed = false;
			resetSprite();
			restart();
			return;
		}
		else
			boomEffect();

	Tank::draw(window);


	if (!m_destroyed && m_lifeTime > sf::milliseconds(1000) && m_lifeTime < sf::milliseconds(5000))
	{
		const sf::IntRect tempIntRect = m_sprite.getTextureRect();
		shieldEffect();
		Tank::draw(window);
		m_sprite.setTexture(sheetsController->playerTank->getSheets());
		m_sprite.setTextureRect(tempIntRect);

	}


}

void Player::damage()
{
	if (m_lifeTime < sf::milliseconds(5000) || m_onShield)
		return;
	else
		Tank::damage();
}

int Player::getLife() const
{
	return m_life;
}

void Player::newGame()
{
	m_animationTime = sf::milliseconds(50);
	m_bulletTime = sf::seconds(1);
	//m_rank = 0;
	//m_intRects = sheetsController->playerTank->getData()[m_rank];
	m_life = START_LIFE;
	m_speed = PLAYER_SPEED;
	restart();
}

/*void Player::killedEnemy()
{
	m_kills++;
	if (m_kills % 5 == 0)
		newRank();
}*/

void Player::destroy()
{
	m_armor = 1;
	m_life--;
	Tank::destroy();
}


void Player::shieldEffect()
{
	m_sprite.setTexture(sheetsController->tankEffects->getSheets());
	m_sprite.setTextureRect(*sheetsController->tankEffects->getData()[(rand() % 2) + 4]);
}

/*void Player::newRank()
{
	if (m_rank == 3)
		return;
	m_rank++;
	m_armor++;
	m_speed += m_rank * 10;
	m_animationTime -= sf::milliseconds(5);
	m_bulletTime -= sf::milliseconds(100);
	m_intRects = sheetsController->playerTank->getData()[m_rank];
}*/
