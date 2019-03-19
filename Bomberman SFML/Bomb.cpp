#include "Bomb.h"

Bomb::Bomb(const sf::Vector2f & pos, const sf::Texture& sheets)
	:UnmoveableObject(pos, sheets), m_sheets(sheets) , m_boomed(false), m_destroyed(false), m_damaged(false)

{
	//GUARD_X =0, GUARD_Y=100
	setType(BOMB, sf::IntRect(FOURTH, EIGHTH, OBJECTIMGSIZE, OBJECTIMGSIZE));

}

bool Bomb::finished()
{

	if (m_boomed && m_clock.getElapsedTime().asSeconds() > BOOMTIME)
		return true;

	if (m_clock.getElapsedTime().asSeconds() >= BOMBTIME)
		m_destroyed = true;


	if (m_clock.getElapsedTime().asMilliseconds() % 1000 < 250)
		setSize(0.85f);
	else if (m_clock.getElapsedTime().asMilliseconds() % 1000 > 500 &&
		m_clock.getElapsedTime().asMilliseconds() % 1000 < 750)
		setSize(0.9f);
	else
		setSize(1.0f);

	return false;

}

bool Bomb::isDestroyed()
{
	return m_destroyed;
}

void Bomb::destroy()
{
	m_destroyed = true;
}

bool Bomb::isBoomed()
{
	return m_boomed;
}

void Bomb::boom(std::vector<std::unique_ptr<Object>>& staticObjects)
{
	m_boomPlaces.push_back(getPosition());
	m_boomPlaces.push_back({ getPosition().x + OBJECTSIZE, getPosition().y });
	m_boomPlaces.push_back({ getPosition().x - OBJECTSIZE, getPosition().y });
	m_boomPlaces.push_back({ getPosition().x, getPosition().y + OBJECTSIZE });
	m_boomPlaces.push_back({ getPosition().x, getPosition().y - OBJECTSIZE });


	for (size_t i = 0; i < m_boomPlaces.size(); i++)
		for (size_t j = 0; j < staticObjects.size(); j++)
			if (staticObjects[j]->getType() == WALL && staticObjects[j]->getShape().getGlobalBounds().contains(m_boomPlaces[i]))
			{
				m_boomPlaces.erase(m_boomPlaces.begin() + i);
				i--;
				break;
			}
			else if (staticObjects[j]->getType() == ROCK && staticObjects[j]->collision(createBoomPlace(m_boomPlaces[i])))
			{
				staticObjects.erase(staticObjects.begin() + j);
				m_damaged = true;
				j--;
			}

	m_boomed = true;
	m_clock.restart();
}

void Bomb::setDamaged()
{
	m_damaged = true;
}

bool Bomb::damagedRobot()
{
	return m_damaged;
}

bool Bomb::isInRange(sf::Sprite object)
{
	for (size_t i = 0; i < m_boomPlaces.size(); i++)
		if (createBoomPlace(m_boomPlaces[i]).getGlobalBounds().intersects(object.getGlobalBounds()))
				return true;
	return false;
}

sf::Sprite Bomb::createBoomPlace(sf::Vector2f pos) const
{
	sf::Sprite sprite(m_sheets, sf::IntRect(FIRST, NINETH, OBJECTIMGSIZE, OBJECTIMGSIZE));

	sprite.setPosition(pos);
	return sprite;
}

void Bomb::draw(sf::RenderWindow & window)
{
	if (!m_destroyed)
		window.draw(getShape());
	else
		for (size_t i = 0; i < m_boomPlaces.size(); i++)
			window.draw(createBoomPlace(m_boomPlaces[i]));
}


