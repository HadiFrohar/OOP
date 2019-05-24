#include "Controller.h"
#include <algorithm>

Controller::Controller()
	:m_board(std::make_unique<Board>()), m_shapeController(std::make_unique<ShapesController>()),
	m_user(std::make_unique<User>()), m_computer(std::make_unique<Computer>()),
	m_colorController(m_shapeController->getColorController()),
	m_userToPlay(true), m_gameFinished(false), m_gameRestart(false)
{
	createPlayersTexts();
	createGameButtons();
	createGame();
}



void Controller::run()
{

	while (m_board->getWindow().isOpen() & !m_gameFinished & !m_gameRestart)
	{
		if (m_user->getScore() >= 0.5)
			break;
		else if (m_computer->getScore() >= 0.5)
			break;
		if (!m_userToPlay)
			computerTurn();

		HandleEvents();
		draw();
	}

	if (m_gameRestart)
		restartGame();
	else
		m_board->getWindow().close();
}


void Controller::createGame()
{

	m_shapeController->createShapes();

	auto playerShape = m_shapeController->getShape(DOWN_LEFT);
	m_user->updateColor(m_colorController->getPair((*playerShape)->getUsedColor()));
	m_user->addShape(*playerShape);

	auto computerShape = m_shapeController->getShape(TOP_RIGHT);
	m_computer->updateColor(m_colorController->getPair((*computerShape)->getUsedColor()));
	m_computer->addShape(*computerShape);

	checkStartUsedColors();

	m_user->play(m_shapeController->getShapes(), m_shapeController->getNearbyMap());
	m_user->updateScore((unsigned)m_shapeController->getShapes().size());
	m_computer->play(m_shapeController->getShapes(), m_shapeController->getNearbyMap());
	m_computer->updateScore((unsigned)m_shapeController->getShapes().size());

}


void Controller::createGameButtons()
{

	m_colorButtons.resize(6);

	m_colorButtons[RED] = ColorRectangle(m_colorController->getColor(RED).first, { (float)(m_user->getText().getPosition().x) + 6 * SHAPE_SIZE,10 }, 1.5*SHAPE_SIZE);
	m_colorButtons[ORANGE] = ColorRectangle(m_colorController->getColor(ORANGE).first, { (float)(m_colorButtons[Color::RED].getShape().getPosition().x + 1.8*SHAPE_SIZE),10 }, 1.5*SHAPE_SIZE);
	m_colorButtons[YELLOW] = ColorRectangle(m_colorController->getColor(YELLOW).first, { (float)(m_colorButtons[Color::ORANGE].getShape().getPosition().x + 1.8 * SHAPE_SIZE),10 }, 1.5*SHAPE_SIZE);
	m_colorButtons[GREEN] = ColorRectangle(m_colorController->getColor(GREEN).first, { (float)(m_colorButtons[Color::YELLOW].getShape().getPosition().x + 1.8 * SHAPE_SIZE),10 }, 1.5*SHAPE_SIZE);
	m_colorButtons[BLUE] = ColorRectangle(m_colorController->getColor(BLUE).first, { (float)(m_colorButtons[Color::GREEN].getShape().getPosition().x + 1.8 * SHAPE_SIZE),10 }, 1.5*SHAPE_SIZE);
	m_colorButtons[PINK] = ColorRectangle(m_colorController->getColor(PINK).first, { (float)(m_colorButtons[Color::BLUE].getShape().getPosition().x + 1.8 * SHAPE_SIZE),10 }, 1.5*SHAPE_SIZE);

	m_gameButtons.push_back(std::make_unique<sf::Text>(m_board->createText(m_board->getRegularFont(), WHITE, { 5,0 }, "EXIT", (unsigned)(FONT_SIZE*1.5))));
	m_gameButtons.push_back(std::make_unique<sf::Text>(m_board->createText(m_board->getRegularFont(), WHITE, { 5,30 }, "RESTART", (unsigned)(FONT_SIZE*1.5))));
}


void Controller::restartGame()
{
	m_gameRestart = false;
	m_user->clear();
	m_computer->clear();

	for (auto &colorButtom : m_colorButtons)
		colorButtom.enable();

	createGame();
	run();
}

void Controller::createPlayersTexts()
{
	m_user->addText(m_board->createText(m_board->getRegularFont(), WHITE,
		{ (float)(1 - TEXT_POS_SCALE)*WINDOWSIZE, (float)(1 - BOARD_SCALE)*WINDOWSIZE / 5 }, "", FONT_SIZE));

	m_computer->addText(m_board->createText(m_board->getRegularFont(), WHITE,
		{ (float)(1 - TEXT_POS_SCALE)*WINDOWSIZE, (float)(1 - BOARD_SCALE)*WINDOWSIZE / 2 }, "", FONT_SIZE));
}


void Controller::checkStartUsedColors()
{
	m_colorButtons[m_colorController->id(m_user->getUsedColor())].disable();
	m_colorButtons[m_colorController->id(m_computer->getUsedColor())].disable();
}

void Controller::HandleEvents()
{
	sf::Event event;
	if (m_board->getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_board->getWindow().close();
			exit(EXIT_SUCCESS);
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				mouseClick(m_board->getWindow().mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
			break;
		}
	}
}

void Controller::draw()
{
	m_board->clear();

	m_user->draw(m_board->getWindow());
	m_computer->draw(m_board->getWindow());

	for (auto &it : m_colorButtons)
		m_board->getWindow().draw(it.getShape());

	m_shapeController->draw(m_board->getWindow());

	for (auto &it : m_gameButtons)
		m_board->getWindow().draw(*it);

	m_board->getWindow().display();
}

void Controller::mouseClick(const sf::Vector2f & pos)
{

	if (m_gameButtons[0]->getGlobalBounds().contains(pos))
		m_gameFinished = true;
	else if (m_gameButtons[1]->getGlobalBounds().contains(pos))
		m_gameRestart = true;
	else if (m_userToPlay)
		for (size_t i = 0; i < m_colorButtons.size(); i++)
			if (m_colorButtons[i].enabled() && m_colorButtons[i].getShape().getGlobalBounds().contains(pos))
			{
				m_colorButtons[i].disable();
				m_colorButtons[m_colorController->id(m_user->getUsedColor())].enable();
				m_user->updateColor(m_colorController->getColor((unsigned)i));

				m_user->play(m_shapeController->getShapes(), m_shapeController->getNearbyMap());
				m_user->updateScore((unsigned)m_shapeController->getShapes().size());
				m_userToPlay = false;
			}

}


void Controller::computerTurn()
{
	std::vector<std::pair<int, int>> colorsList = m_computer->nearbyColorsCount(m_shapeController->getShapes(), m_shapeController->getNearbyMap(), m_colorController);

	for(size_t i=0; i<colorsList.size(); i++)
		if (!m_colorButtons[colorsList[i].first].enabled())
		{
			colorsList.erase(colorsList.begin() + i);
			continue;
		}
		else
		{
			m_colorButtons[m_colorController->id(m_computer->getUsedColor())].enable();
			m_colorButtons[colorsList[i].first].disable();
			m_computer->updateColor(m_colorController->getColor(colorsList[i].first));
			m_computer->play(m_shapeController->getShapes(), m_shapeController->getNearbyMap());
			m_computer->updateScore((unsigned)m_shapeController->getShapes().size());
			m_userToPlay = true;
			break;
		}
}

