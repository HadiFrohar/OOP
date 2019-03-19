#include "Board.h"



Board::Board()
	: m_window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "Bomberman")
{
	loadResc();
	m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
	m_backgroundImg.setRepeated(true);
	m_background.setTexture(m_backgroundImg);
	m_background.setTextureRect(sf::IntRect(0, 0, (unsigned)m_size, (unsigned)m_size));


}

void Board::draw(std::vector<std::unique_ptr<Object>> &staticObjects, std::vector<Guard> &guards, Robot &robot, Door &door, std::vector<Bomb> &bombs, std::vector<Box> &statusBar)
{
	clear();

	for (auto guard : guards)
		guard.draw(m_window);


	for (auto bomb : bombs)
		bomb.draw(m_window);

	door.draw(m_window);

	for (const auto& object : staticObjects)
		object->draw(m_window);

	robot.draw(m_window);

	for (auto box : statusBar)
		box.draw(m_window);

	m_window.display();
}

void Board::clear()
{
	m_window.clear();
	m_window.draw(m_background);
	m_window.setView(m_view);

}

void Board::adjustSize(unsigned int size, bool menu)
{
	float newSize = (float)size * OBJECTSIZE;
	if (newSize >= WINDOWSIZE || newSize == EMPTY)
		m_size = WINDOWSIZE;
	else
		m_size = newSize;

	if(menu)
		m_backgroundImg.loadFromImage(m_backgroundSheet, sf::IntRect(FIRST, FIRST, OBJECTIMGSIZE, OBJECTIMGSIZE));
	else
		m_backgroundImg.loadFromImage(m_backgroundSheet, sf::IntRect(m_backgroundPos, FIRST, OBJECTIMGSIZE, OBJECTIMGSIZE));
	//m_background.setSize({ m_size, m_size });
	m_view.reset(sf::FloatRect(0, 0, m_size, m_size));
	m_window.setView(m_view);
}

float Board::getSize()
{
	return m_size;
}

void Board::moveView(int direction)
{
	if (direction == 0)
		m_view.move(OBJECTSIZE, 0);
	else if (direction == 1)
		m_view.move(-(signed)OBJECTSIZE, 0);
	else if (direction == 2)
		m_view.move(0, OBJECTSIZE);
	else if (direction == 3)
		m_view.move(0, -(signed)OBJECTSIZE);

}

void Board::adjustView(Robot & robot)
{
	if (robot.getPosition().x > m_size)
		m_view.move(robot.getPosition().x - m_size + OBJECTSIZE * 2, 0);

	if (robot.getPosition().y > m_size)
		m_view.move(0, robot.getPosition().y - m_size + OBJECTSIZE * 2);
}

sf::View & Board::getView()
{
	return m_view;
}


bool Board::isOn()
{
	return m_window.isOpen();
}

void Board::loadResc()
{
	if (!m_sheets.loadFromFile(SHEETSPATH))
		loadCrash();

	if (!m_font.loadFromFile(USEDFONT))
		loadCrash();

	if (!m_icon.loadFromFile(ICONPATH))
		loadCrash();

	if (!m_backgroundSheet.loadFromFile(BACKGROUNDPATH))
		loadCrash();
}

void Board::newBackground()
{
	srand((unsigned)time(NULL));
	m_backgroundPos = (rand() % 3)*100;
}

sf::RenderWindow & Board::getWindow()
{
	return m_window;
}

sf::Texture & Board::getSheets()
{
	return m_sheets;
}

sf::Font & Board::getFont()
{
	return m_font;
}

sf::Image & Board::getIcon()
{
	return m_icon;
}

