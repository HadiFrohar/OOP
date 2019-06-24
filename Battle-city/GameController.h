#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Util.h"
#include "SheetsController.h"
#include "StageController.h"
#include "FontController.h"
#include "Menu.h"
#include "Object.h"
#include "Wall.h"
#include "Player.h"
#include "Basement.h"
#include "Enemy.h"
#include "SideBar.h"

class GameController
{
public:
	GameController();
	void run();

private:
	void newGame();
	void gameOver();
	void newLevel();
	void checkTanks();
	void HandleEvents();
	void draw();

	unique_ptr<Tank> randomizeEnemy(const sf::Vector2f &pos);

	unique_ptr<SheetsController> m_sheetsController;
	unique_ptr<StageController> m_stageController;
	unique_ptr<FontController> m_fontController;
	unique_ptr<Menu> m_menu;
	unique_ptr<SideBar> m_sideBar;

	unique_ptr<sf::RectangleShape> m_gameBoard;
	unique_ptr<sf::RenderWindow> m_window;
	
	vector<unique_ptr<Object>> m_fixedObjects;
	
	vector<unique_ptr<Tank>> m_tanks;
	unique_ptr<Basement> m_basement;

	sf::Clock m_clock;
	sf::Time m_time1, m_time2, m_dt;
	sf::Time m_pSpawnTime;

	int m_enemiesLeft, m_enemiesCount, m_stageId;
};

