#pragma once
#include <SFML/Graphics.hpp>
class Board
{
public:
	Board();
	~Board();

	void clear(); //clears the window (only background will be there)

	sf::RenderWindow & getWindow(); //returns the window
	sf::Font & getGameFont(); //returns SEGA FONT
	sf::Font & getRegularFont(); //returns Arial font

	//creates text for the game
	sf::Text createText(const sf::Font &font, const sf::Color &color, const sf::Vector2f &pos, std::string str, const unsigned size) const;

private:
	void loadRc(); //load resources, we have only fonts
	void createGameBoard(); //creates game rectangle (part of the window)



	sf::RenderWindow m_window; //main window
	sf::RectangleShape m_gameBoard; //game rectangle
	sf::Font m_gameFont; //sega font
	sf::Font m_regualrFont; //arial font
};

