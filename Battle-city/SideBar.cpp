#include "SideBar.h"
#include "Util.h"
SideBar::SideBar(SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>* sieBarIcons, sf::Font * font)
	:m_sieBarIcons(sieBarIcons)
{
	m_sprite.setTexture(m_sieBarIcons->getSheets());
	m_text.setFont(*font);
	m_text.setStyle(sf::Text::Style::Bold);
	m_text.setCharacterSize(20);
	m_text.setFillColor(sf::Color::Black);
}

void SideBar::draw(sf::RenderWindow * window, int enemies, int life, int stage)
{
	drawEnemiesCount(window, enemies);
	drawLifeStatus(window, life);
	drawStageInfo(window, stage);
}

void SideBar::drawEnemiesCount(sf::RenderWindow * window, int enemies)
{
	m_sprite.setTextureRect(*m_sieBarIcons->getData()[2]);
	float y = (float)(GAMEBOARD_SIZE*0.1);
	for (int i = 0; i < (enemies / 2 + enemies % 2); i++)
	{
		y += (float)(m_sprite.getGlobalBounds().height*1.2);
		float x = (float)(GAMEBOARD_SIZE*1.1);
		for (int j = 0; j < 2; j++)
		{
			x += (float)(j * m_sprite.getGlobalBounds().width*1.2);
			m_sprite.setPosition(x, y);
			window->draw(m_sprite);
			if (enemies % 2 == 1 && i == (enemies / 2 + enemies % 2) - 1)
				break;
		}
	}
}

void SideBar::drawLifeStatus(sf::RenderWindow * window, int life)
{
	m_text.setString("IP");
	m_text.setPosition({ (float)(GAMEBOARD_SIZE*1.1),(float)(GAMEBOARD_SIZE*0.6) });
	window->draw(m_text);

	m_text.setString(std::to_string(life));
	m_text.setPosition({ (float)(GAMEBOARD_SIZE*1.15),(float)(GAMEBOARD_SIZE*0.66) });
	m_sprite.setTextureRect(*m_sieBarIcons->getData()[1]);
	m_sprite.setPosition({ (float)(GAMEBOARD_SIZE*1.1),(float)(GAMEBOARD_SIZE*0.67) });
	window->draw(m_sprite);
	window->draw(m_text);
}

void SideBar::drawStageInfo(sf::RenderWindow * window, int stage)
{
	m_text.setString(std::to_string(stage));
	m_text.setPosition({ (float)(GAMEBOARD_SIZE*1.15),(float)(GAMEBOARD_SIZE*0.9) });
	m_sprite.setTextureRect(*m_sieBarIcons->getData()[0]);
	m_sprite.setPosition({ (float)(GAMEBOARD_SIZE*1.1),(float)(GAMEBOARD_SIZE*0.84) });
	window->draw(m_sprite);
	window->draw(m_text);
}
