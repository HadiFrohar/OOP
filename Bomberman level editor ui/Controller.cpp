#include "Controller.h"
#include "Utilities.h"
#include <cmath>

Controller::Controller()
	: m_window(sf::VideoMode(800, 800), "Bomberman Level Editor")
{
	m_type = NOTYPE;
	m_newFile = false;

}

void Controller::run()
{
	m_cmdWND = GetConsoleWindow();
	ShowWindow(m_cmdWND, SW_HIDE);

	createButtons();
	draw();
	m_file.open(MAPPATH);
	if (!m_file)
		newMap();

	if (!m_file)
	{
		perror("Couldn't create file");
		exit(EXIT_FAILURE);
	}
	if (!m_newFile)
		m_map = getMap(m_file, m_size, m_steps);
	else
		m_map = createEmptyMap(m_size);

	readElements();

	while (m_window.isOpen())
	{
		draw();
		HandleEvents();
	}
}

void Controller::HandleEvents()
{
	sf::Event event;
	if (m_window.waitEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if(click(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
					updateElements();
			}
			break;
		case sf::Event::MouseMoved:
			if (m_type == removeType)
				checkMouseOver({ (float)event.mouseMove.x, (float)event.mouseMove.y });
			break;
		}
	}
}

void Controller::draw()
{
	m_window.clear(sf::Color(23,131,33,255));
	drawLines();

	for (size_t i = 0; i < m_buttons.size(); ++i)
	{
		m_buttons[i].draw(m_window);
	}

	for (size_t i = 0; i < m_guards.size(); ++i)
	{
		m_guards[i].draw(m_window);
	}

	for (size_t i = 0; i < m_rocks.size(); ++i)
	{
		m_rocks[i].draw(m_window);
	}

	for (size_t i = 0; i < m_walls.size(); ++i)
	{
		m_walls[i].draw(m_window);
	}

	if(m_robot.isUsed())
		m_robot.draw(m_window);

	if(m_door.isUsed())
		m_door.draw(m_window);

	m_window.display();
}

bool Controller::click(sf::Vector2f pos)
{
	for (size_t i = 0; i < m_buttons.size(); ++i)
	{
		if (m_buttons[i].click(pos))
		{
			if (m_type == i)
				m_type = NOTYPE;
			else
				m_type = (int) i;
			for (size_t j = 0; j < m_buttons.size(); j++)
				if (i != j)
					m_buttons[j].unclick();

			if (m_type == emptyAll)
			{
				char c;
				ShowWindow(m_cmdWND, SW_SHOW);

				m_buttons[emptyAll].unclick();
				m_type = NOTYPE;


				std::cout << "Are you sure you want to clear the map? (y to clear): ";
				std::cin >> c;
				if (c != 'y' && c!='Y')
				{
					ShowWindow(m_cmdWND, SW_HIDE);
					system("CLS");
					return false;
				}
				newMap();
				m_map = createEmptyMap(m_size);
				readElements();
				return true;
			}

			return false;
		}
	}


	if (m_type == NOTYPE || pos.x > (DEFAULT_SIZE*m_size) || pos.y < GAME_Y_POS || pos.y>(GAME_Y_POS + DEFAULT_SIZE * m_size))
		return false;



	if (m_type == removeType)
	{

		size_t index = 0;

		if (m_robot.click(pos))
		{
			m_robot.remove();
			return true;
		}
		else if (m_door.click(pos))
		{
			m_door.remove();
			return true;
		}

		for (size_t i = 0; i < m_guards.size(); ++i)
			if (m_guards[i].click(pos))
			{
				m_guards.erase(m_guards.begin() + i);
				return true;
			}
		for (size_t i = 0; i < m_rocks.size(); ++i)
			if (m_rocks[i].click(pos))
			{
				m_rocks.erase(m_rocks.begin() + i);
				return true;
			}
		for (size_t i = 0; i < m_walls.size(); ++i)
			if (m_walls[i].click(pos))
			{
				m_walls.erase(m_walls.begin() + i);
				return true;
			}

	}

	pos.x =(float)(pos.x - fmod(pos.x, DEFAULT_SIZE));
	pos.y =(float)(pos.y - fmod(pos.y, DEFAULT_SIZE));

	if (placeIsTaken(pos))
		return false;

	if (m_type == robotType)
		m_robot.use(pos);
	else if (m_type == doorType)
		m_door.use(pos);
	
	if (m_type == guardType)
		m_guards.push_back(Guard(pos));
	else if (m_type == rockType)
		m_rocks.push_back(Rock(pos));
	else if (m_type == wallType)
		m_walls.push_back(Wall(pos));

	return true;
}

void Controller::createButtons()
{
	m_buttons.push_back(Button({ 3, 3 }, ROBOTPATH));
	m_buttons.push_back(Button({ 60, 3 }, GUARDPATH));
	m_buttons.push_back(Button({ 117, 3 }, ROCKPATH));
	m_buttons.push_back(Button({ 174, 3 }, DOORPATH));
	m_buttons.push_back(Button({ 231, 3 }, WALLPATH));
	m_buttons.push_back(Button({ 288, 3 }, TRASHPATH));
	m_buttons.push_back(Button({ 345, 3 }, EMPTYALLPATH));
}

void Controller::clearElements()
{
	m_guards.clear();
	m_rocks.clear();
	m_rocks.clear();
	m_walls.clear();
	m_robot.remove();
	m_door.remove();
}

void Controller::readElements()
{
	clearElements();

	for (size_t i = 0; i < m_map.size(); i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			sf::Vector2f pos;
			pos.x = (float)(DEFAULT_SIZE*j);
			pos.y = (float)(DEFAULT_SIZE*i + GAME_Y_POS);

			if (m_map[i][j] == ROBOT)
				m_robot.use(pos);
			else if (m_map[i][j] == DOOR)
				m_door.use(pos);
			else if (m_map[i][j] == GUARD)
				m_guards.push_back(Guard(pos));
			else if (m_map[i][j] == ROCK)
				m_rocks.push_back(Rock(pos));
			else if (m_map[i][j] == WALL)
				m_walls.push_back(Wall(pos));

		}
	}
	updateElements();
}

void Controller::updateElements()
{
	m_map.clear();

	for (int i = 0; i < m_size; i++)
	{

		std::string line(m_size, WHITESPACE);
		m_map.push_back(line);
	}


	writeOnMap(m_map, std::vector<Object>(m_guards.begin(), m_guards.end()));
	writeOnMap(m_map, std::vector<Object>(m_walls.begin(), m_walls.end()));
	writeOnMap(m_map, std::vector<Object>(m_rocks.begin(), m_rocks.end()));
	if(m_robot.isUsed())
		writeOnMapChar(m_map, m_robot.getPosition(), ROBOT);
	if(m_door.isUsed())
		writeOnMapChar(m_map, m_door.getPosition(), DOOR);

	updateMapInFile(m_map, m_size, m_steps);

}

bool Controller::placeIsTaken(sf::Vector2f pos)
{



	if (m_robot.getPosition() == pos || m_door.getPosition() == pos)
		return true;

	
	if (hasPoint(std::vector<Object>(m_guards.begin(), m_guards.end()), pos) ||
		hasPoint(std::vector<Object>(m_walls.begin(), m_walls.end()), pos) ||
		hasPoint(std::vector<Object>(m_rocks.begin(), m_rocks.end()), pos))
		return true;

	return false;
}

void Controller::newMap()
{
	m_map.clear();
	ShowWindow(m_cmdWND, SW_SHOW);
	std::cout << "Please enter the size of the map: ";
	std::cin >> m_size;
	std::cout << "Please enter how many steps for the level: ";
	std::cin >> m_steps;

	m_newFile = true;
	m_file.open(MAPPATH, std::ios::out | std::ios::trunc);
	ShowWindow(m_cmdWND, SW_HIDE);
	system("CLS");
	m_file.close();

}

void Controller::checkMouseOver(sf::Vector2f pos)
{

	unhoverElements(pos);

	if (m_robot.click(pos))
	{
		m_robot.mouseOver();
		return;
	}
	if (m_door.click(pos))
	{
		m_door.mouseOver();
		return;
	}

	for (size_t i = 0; i < m_guards.size(); i++)
		if (m_guards[i].click(pos))
		{
			m_guards[i].mouseOver();
			return;
		}

	for (size_t i = 0; i < m_rocks.size(); i++)
		if (m_rocks[i].click(pos))
		{
			m_rocks[i].mouseOver();
			return;
		}

	for (size_t i = 0; i < m_walls.size(); i++)
		if (m_walls[i].click(pos))
		{
			m_walls[i].mouseOver();
			return;
		}

}

void Controller::unhoverElements(const sf::Vector2f & pos)
{
	if (m_robot.getPosition() != pos)
		m_robot.mouseNotOver();

	if (m_door.getPosition() != pos)
		m_door.mouseNotOver();


	for (size_t i = 0; i < m_guards.size(); i++)
		if (m_guards[i].getPosition() != pos)
			m_guards[i].mouseNotOver();

	for (size_t i = 0; i < m_rocks.size(); i++)
		if (m_rocks[i].getPosition() != pos)
			m_rocks[i].mouseNotOver();

	for (size_t i = 0; i < m_walls.size(); i++)
		if (m_walls[i].getPosition() != pos)
			m_walls[i].mouseNotOver();
}

void Controller::drawLines()
{
	for (int i = 0; i < m_size; i++)
	{
		sf::Vertex horLine[] =
		{
			sf::Vertex(sf::Vector2f(0, (float)DEFAULT_SIZE*i + GAME_Y_POS), sf::Color::Black),
			sf::Vertex(sf::Vector2f((float)DEFAULT_SIZE*m_size, (float)DEFAULT_SIZE*i + GAME_Y_POS), sf::Color::Black)

		};
		sf::Vertex verLine[] =
		{
			sf::Vertex(sf::Vector2f((float)DEFAULT_SIZE*i, GAME_Y_POS), sf::Color::Black),
			sf::Vertex(sf::Vector2f((float)DEFAULT_SIZE*i, (float)DEFAULT_SIZE*m_size+GAME_Y_POS), sf::Color::Black)

		};

		m_window.draw(horLine, 2, sf::Lines);
		m_window.draw(verLine, 2, sf::Lines);


	}
}

