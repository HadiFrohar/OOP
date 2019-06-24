#include "GameController.h"
#include "EnemyArmor.h"
#include "EnemyBasic.h"
#include "EnemyFast.h"
#include "EnemyPower.h"

using std::make_unique;

GameController::GameController()
	:m_window(make_unique<sf::RenderWindow>(sf::VideoMode(GAMEBOARD_SIZE + 100, GAMEBOARD_SIZE + 50), "Battle City")),
	m_sheetsController(make_unique<SheetsController>()), m_fontController(make_unique<FontController>()),
	m_stageController(make_unique<StageController>(m_sheetsController.get())),
	m_menu(make_unique<Menu>(m_sheetsController->gameWords.get(), m_fontController->getPressStartFont())),
	m_sideBar(make_unique<SideBar>(m_sheetsController->sidebarIcons.get(), m_fontController->getPressStartFont())),
	m_gameBoard(make_unique<sf::RectangleShape>()),
	m_basement(make_unique<Basement>(sf::Vector2f(217, 409), m_sheetsController->baseIcon->getSheets(),
		std::make_pair(m_sheetsController->baseIcon->getData()[0], m_sheetsController->baseIcon->getData()[1])))
{
	Object::updateSheetsController(m_sheetsController.get());
	m_gameBoard->setFillColor(sf::Color::Black);
	m_gameBoard->setSize({ (float)GAMEBOARD_SIZE, (float)GAMEBOARD_SIZE });
	m_gameBoard->setPosition({ 25,25 });
	srand((unsigned)time(NULL));
	m_pSpawnTime = sf::seconds(2);

	m_tanks.emplace_back(make_unique<Player>(PLAYER_POSITION));
}

void GameController::run()
{
	m_menu->showMenu(m_window.get());
	newGame();
	while (m_stageController->loadStage(m_fixedObjects))
	{
		newLevel();
		while (m_window->isOpen())
		{
			if (m_basement->isDestroyed() || dynamic_cast<Player*>(m_tanks[0].get())->getLife() <= 0)
				return gameOver();
			if (m_enemiesLeft == 0)
				break;
			m_time2 = m_clock.getElapsedTime();
			m_dt = m_time2 - m_time1;
			m_time1 = m_time2;
			checkTanks();
			HandleEvents();
			m_time1 = m_clock.getElapsedTime();
			for (auto &tank : m_tanks)
				tank->move(m_fixedObjects, m_gameBoard.get(), m_tanks, m_basement.get(), m_dt);

			draw();
		}
	}


}


void GameController::newGame()
{
	dynamic_cast<Player*>(m_tanks[0].get())->newGame();
	m_basement->restart();
	m_stageController->restart();
}

void GameController::gameOver()
{
	newLevel();
	draw();
	sf::Sprite game_over;
	game_over.setTexture(m_sheetsController->gameWords->getSheets());
	game_over.setTextureRect(*m_sheetsController->gameWords->getData()[1]);
	game_over.setPosition({ GAMEBOARD_SIZE / 3, GAMEBOARD_SIZE / 3 });
	m_window->draw(game_over);
	m_window->display();
	m_time1 = m_clock.getElapsedTime();

	while ((m_clock.getElapsedTime() - m_time1) < sf::seconds(5))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

	run();
}

void GameController::newLevel()
{
	m_tanks[0]->restart();
	m_tanks.erase(m_tanks.begin() + 1, m_tanks.end());
	m_enemiesCount = 0;
	m_enemiesLeft = ENEMIES_COUNT;
	m_stageId = m_stageController->getStageId();
	m_time1 = m_clock.getElapsedTime();
}



void GameController::checkTanks()
{
	m_pSpawnTime += m_dt;

	for (auto it = m_tanks.begin(); it != m_tanks.end(); )
		if ((*it)->isBoomed())
		{
			m_enemiesLeft--;
			it = m_tanks.erase(it);
		}
		else
			++it;

	if (m_pSpawnTime < sf::seconds(1) || m_enemiesCount == ENEMIES_COUNT || m_tanks.size() == 5)
		return;

	m_tanks.emplace_back(randomizeEnemy(m_stageController->getSpawnPos()));
	m_pSpawnTime = sf::Time::Zero;

}

void GameController::HandleEvents()
{
	sf::Event event;
	if (m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_menu->pause(m_window.get());
			}
			break;

		}
	}
}

void GameController::draw()
{
	m_window->clear(GREY);
	m_window->draw(*m_gameBoard);
	dynamic_cast<Player*>(m_tanks[0].get());
	m_sideBar->draw(m_window.get(), m_enemiesLeft, dynamic_cast<Player*>(m_tanks[0].get())->getLife(), m_stageId);

	for (auto &tank : m_tanks)
			tank->draw(m_window.get());

	for (auto &object : m_fixedObjects)
		object->draw(m_window.get());

	m_basement->draw(m_window.get());

	m_window->display();
}

unique_ptr<Tank> GameController::randomizeEnemy(const sf::Vector2f & pos)
{

	int r = rand() % 10;
	unique_ptr<Enemy> enemy;
	if (r == 0 || r == 3 || r == 8)
		enemy = make_unique<EnemyBasic>(pos);
	else if (r == 5 || r == 2 || r == 7)
		enemy = make_unique<EnemyPower>(pos);
	else if (r == 1 || r == 6)
		enemy = make_unique<EnemyFast>(pos);
	else if (r == 4 || r == 9)
		enemy = make_unique<EnemyArmor>(pos);

	m_enemiesCount++;

	return enemy;
}
