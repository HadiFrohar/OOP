#pragma once
#include <SFML/Graphics.hpp>
#include "SheetsCfg.h"
class SideBar
{
public:
	SideBar(SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>* sieBarIcons, sf::Font *font);

	//draws side bar (game statistics)
	void draw(sf::RenderWindow *window, int enemies, int life, int stage);
private:
	void drawEnemiesCount(sf::RenderWindow * window, int enemies); //for enemies left
	void drawLifeStatus(sf::RenderWindow * window, int life); //for player life
	void drawStageInfo(sf::RenderWindow * window, int stage); //for stage

	SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>* m_sieBarIcons; //side bar sheets configuration object

	sf::Text m_text; //side bar text
	sf::Sprite m_sprite; //side bar sprite
};

