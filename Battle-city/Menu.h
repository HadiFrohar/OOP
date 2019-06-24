#pragma once
#include <SFML/Graphics.hpp>
#include "SheetsCfg.h"


class Menu
{
public:
	Menu(SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>> *menuWords, sf::Font *font);
	void showMenu(sf::RenderWindow* window); //shows game menu
	void pause(sf::RenderWindow* window); //updates menu as a pause menu

	static void hoverText(sf::Text &text); //animates menu text

private:


	SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>> *m_menuWords;
	
	sf::Text m_menuText;
	sf::Sprite m_gameIcon;

	sf::Clock m_menuClock;

};

