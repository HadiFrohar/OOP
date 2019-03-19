#include "Controller.h"
#include <sstream>
#include <iostream>

Controller::Controller(Board &board, Menu &menuPage)
	:m_board(board), m_menuPage(menuPage)
{
}

Controller::~Controller()
{
	
}

void Controller::loadResc()
{
	m_sheets = m_board.getSheets();
	m_font = m_board.getFont();

	createStatusBar();

	m_robot.setSheets(m_sheets);
	m_door.setSheets(m_sheets);

}

void Controller::run()
{
	loadResc();
	m_robot.setStartLife();
	m_robot.resetScore();

	map.openFile();

	while (map.readMap())
	{
		m_map = map.getMap();
		m_levelTime = map.getTime();
		m_bombsCount = map.getBombsCount();
		m_size = map.getSize();

		m_robot.clear();
		while (!finishedLevel() && m_robot.isAlive())
		{

		}
		if (m_robot.isAlive())
		{
			m_levelScore += m_guardsSize * WINPOINTS;
			m_robot.addScore(m_levelScore);
			m_menuPage.updateStatus(LEVELPASSEDMSG);

			m_menuPage.pause();
			if (!m_board.isOn())
				break;

			m_board.adjustSize(m_size, false);
		}

		if (!m_robot.isAlive())
		{
			m_menuPage.updateStatus(LOSEMSG);
			break;
		}

	}

	map.closeFile();

	if(m_robot.isAlive())
		m_menuPage.updateStatus(WINMSG);

	if (m_board.isOn())
		m_menuPage.playAgain();


}


void Controller::readItemsFromMap()
{
	clearItems();
	for (size_t i = 0; i < m_map.size(); i++)
	{
		for (unsigned int j = 0; j < m_size; j++)
		{
			sf::Vector2f pos;
			pos.x = (float)(OBJECTSIZE*j);
			pos.y = (float)(OBJECTSIZE*i);

			if (m_map[i][j] == ROBOT)
				m_robot.setPoisiton(pos);
			else if (m_map[i][j] == DOOR)
			{
				m_door.setPoisiton(pos);
				m_staticObjects.push_back(std::make_unique<Rock>(pos, m_sheets));
			}
			else if (m_map[i][j] == GUARD)
				m_guards.push_back(Guard(pos, m_sheets));
			else if (m_map[i][j] == ROCK)
				m_staticObjects.push_back(std::make_unique<Rock>(pos, m_sheets));
			else if (m_map[i][j] == WALL)
				m_staticObjects.push_back(std::make_unique<Wall>(pos, m_sheets));
		}
	}

	m_robot.setBombs(m_bombsCount);

}


void Controller::clearItems()
{
	m_staticObjects.clear();
	m_guards.clear();
	m_robot.clear();
	m_door.clear();
	m_bombs.clear();
}

bool Controller::finishedLevel()
{
	readItemsFromMap();

	m_board.newBackground();
	m_board.adjustSize(m_size, false);

	m_board.adjustView(m_robot);
		
	m_guardsSize = (int)m_guards.size();
	m_levelScore = 0;

	m_clock.restart();

	while (m_board.isOn())
	{
		m_robot.move(m_staticObjects, m_bombs, m_board.getView(), (int)m_size*OBJECTSIZE);

		HandleEvents();

		if (m_pausedTime.asSeconds() != 0)
		{
			m_levelTime += (int)m_pausedTime.asSeconds();
			m_pausedTime = m_pausedTime.Zero;
		}

		checkBombs(m_bombs);
		moveGuards();
		checkDamage();
		updateStatusBar();
		draw();
		if (!m_robot.isAlive())
			return false ;
		else if (m_clock.getElapsedTime().asSeconds() >= m_levelTime)
		{
			m_robot.damage();
			return false;
		}

		if (m_robot.win(m_door))
			return true;
	}

	return false;
}


void Controller::HandleEvents()
{
	sf::Event event;
	if (m_board.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_board.getWindow().close();
			map.closeFile();
			exit(EXIT_SUCCESS);
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_menuPage.updateStatus(SCOREMSG + std::to_string(m_robot.getScore()));
				m_pausedClock.restart();
				m_menuPage.pause();
				m_board.adjustSize(m_size, false);
				m_pausedTime = m_pausedClock.getElapsedTime();
			}
			break;
				
		}
	}
}

void Controller::draw()
{

	m_board.draw(m_staticObjects, m_guards, m_robot, m_door, m_bombs, m_statusBar);

}

void Controller::moveGuards()
{
	for (size_t i = 0; i < m_guards.size(); i++)
		m_guards[i].move(m_staticObjects, m_robot, m_door, (int)i);
}

void Controller::checkBombs(std::vector<Bomb>& bombs)
{
	for (size_t i = 0; i < bombs.size(); i++)
		if (bombs[i].finished())
		{
			bombs.erase(bombs.begin() + i);
			i--;
		}
		else if (bombs[i].isDestroyed() && !bombs[i].isBoomed())
			bombs[i].boom(m_staticObjects);

}

void Controller::checkDamage()
{
	for (size_t i = 0; i < m_bombs.size(); i++)
	{
		if (!m_bombs[i].isBoomed())
			continue;

		for (size_t j = 0; j < m_bombs.size(); j++)
			if (i == j)
				continue;
			else if (!m_bombs[j].isBoomed() && m_bombs[i].isInRange(m_bombs[j].getShape()))
				m_bombs[j].destroy();
	}

	for (size_t i=0; i<m_guards.size(); i++)
	{
		m_guards[i].isInRobotRange(m_robot);
		if (m_guards[i].isInBoomRange(m_bombs))
		{
			m_guards.erase(m_guards.begin() + i);
			i--;
			m_levelScore += m_guardsSize * KILLPOINTS;
		}
	}

	if (m_robot.isInBoomRange(m_bombs))
		m_robot.damage();

}

void Controller::createStatusBar()
{
	for (int i = 0; i < 3; i++)
	{
		m_statusBar.push_back(Box({ 0,(float)OBJECTSIZE*i }, m_sheets));
		m_statusBar[i].setImgPosition(sf::IntRect(SECOND*i+OBJECTSIZE, NINETH, OBJECTIMGSIZE, OBJECTIMGSIZE));
		m_statusBar[i].setFont(m_font);
	}

	m_statusBar.push_back(Box({ (float)OBJECTSIZE, 0 }, m_sheets));
	m_statusBar[3].setImgPosition(sf::IntRect(FIRST, TENTH, OBJECTIMGSIZE, OBJECTIMGSIZE));
	m_statusBar[3].setFont(m_font);
}

void Controller::updateStatusBar()
{
	unsigned int time = m_levelTime - (unsigned int)m_clock.getElapsedTime().asSeconds();
	m_statusBar[0].updateText(std::to_string(m_robot.getLife()));
	m_statusBar[1].updateText(std::to_string((time-time%MINUTE)/MINUTE)+":"+ std::to_string(time%MINUTE));
	m_statusBar[2].updateText(std::to_string(m_robot.getScore()+ m_levelScore));
	m_statusBar[3].updateText(std::to_string(m_robot.getBombs()));

	m_statusBar[0].setPosition({ m_board.getView().getCenter().x - m_board.getSize() / 2, m_board.getView().getCenter().y - m_board.getSize()/2 });
	m_statusBar[1].setPosition({ m_board.getView().getCenter().x - m_board.getSize() / 2 + OBJECTSIZE, m_board.getView().getCenter().y - m_board.getSize() / 2 });
	m_statusBar[2].setPosition({ m_board.getView().getCenter().x - m_board.getSize() / 2 + OBJECTSIZE*2, m_board.getView().getCenter().y - m_board.getSize() / 2 });
	m_statusBar[3].setPosition({ m_board.getView().getCenter().x - m_board.getSize() / 2 + OBJECTSIZE*3, m_board.getView().getCenter().y - m_board.getSize() / 2 });

}

