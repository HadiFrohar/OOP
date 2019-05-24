#include "Board.h"
#include "Settings.h"
#include "Exceptions.h"


Board::Board()
	: m_window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "6 Colors")
{
	//m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());
	clear();
	loadRc();
	createGameBoard();
}


Board::~Board()
{
}


void Board::clear()
{
	m_window.clear(BACKGROUNDCOLOR);
	m_window.draw(m_gameBoard);
}

void Board::loadRc()
{
	if (!m_gameFont.loadFromFile(GAMEFONT))
		throw FileNotOpen();
	if (!m_regualrFont.loadFromFile(REGULARFONT))
		throw FileNotOpen();

}

void Board::createGameBoard()
{
	m_gameBoard.setSize({ BOARD_SCALE*WINDOWSIZE, BOARD_SCALE*WINDOWSIZE });
	m_gameBoard.setFillColor(BACKGROUNDCOLOR);
	m_gameBoard.setOutlineThickness(3);
	m_gameBoard.setOutlineColor(BLACK);
	//m_gameBoard.setPosition({ WINDOWSIZE / 2, WINDOWSIZE / 2 });
	m_gameBoard.setPosition({ (float)(1 - BOARD_SCALE) / 2 * WINDOWSIZE,
		(float)(0.99 - BOARD_SCALE)*WINDOWSIZE });
}

sf::RenderWindow & Board::getWindow()
{
	return m_window;
}

sf::Font & Board::getGameFont()
{
	return m_gameFont;
}

sf::Font & Board::getRegularFont()
{
	return m_regualrFont;
}

sf::Text Board::createText(const sf::Font & font, const sf::Color & color, const sf::Vector2f & pos, std::string str, const unsigned size) const
{
	sf::Text text;
	text.setPosition(pos);
	text.setString(str);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(color);
	text.setFont(font);
	text.setCharacterSize(size);
	//text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
	return text;
}
