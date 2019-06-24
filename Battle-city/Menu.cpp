#include "Menu.h"
#include "Util.h"

Menu::Menu(SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>* menuWords, sf::Font *font)
	:m_menuWords(menuWords)
{
	m_menuClock.restart();
	m_gameIcon.setPosition((float)(GAMEBOARD_SIZE / 6), (float)(GAMEBOARD_SIZE / 4));
	m_gameIcon.setTexture(m_menuWords->getSheets());
	m_gameIcon.setTextureRect(*m_menuWords->getData()[0]);

	m_menuText.setFont(*font);
	m_menuText.setFillColor(sf::Color::White);
	m_menuText.setStyle(sf::Text::Style::Bold);
	m_menuText.setCharacterSize(40);
	m_menuText.setString("PLAY");
	m_menuText.setPosition({ m_gameIcon.getPosition().x+100, (float)(m_gameIcon.getPosition().y + 1.5 * m_gameIcon.getGlobalBounds().top) });
}


void Menu::showMenu(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		if (m_menuClock.getElapsedTime().asMilliseconds() > 400)
		{
			hoverText(m_menuText);
			window->clear(sf::Color::Black);
			window->draw(m_gameIcon);
			window->draw(m_menuText);
			window->display();
			m_menuClock.restart();
		}

		sf::Event event;
		if (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
			{
				window->close();
				exit(EXIT_SUCCESS);
			}
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
					break;

	}
}

void Menu::pause(sf::RenderWindow * window)
{
	m_menuText.setString("CONTINUE");
	showMenu(window);
}

void Menu::hoverText(sf::Text &text)
{

	if (text.getFillColor() == sf::Color::White)
		text.setFillColor(sf::Color::Red);
	else
		text.setFillColor(sf::Color::White);
}
