#pragma once
#include "Wall.h"
#include "Board.h"
class Menu
{
public:
	Menu(Board &board); //Menu constructor
	~Menu() {} //Menu destructor

	//draws the items of the menu on the window and displays it
	void display();

	//creates all the images of the menu, (logo, icon, and bomb image)
	void createImages();

	//creates all the texts of the menu (start and exit)
	void createTexts();

	//updates menu to be paused menu
	void pause();

	void playAgain();

	void updateStatus(std::string text);

	//creates wall border for the window
	void createBorder();

	//handle events of the window (close window, press up\down arrow, press enter)
	void HandleEvents(sf::RenderWindow &window);

private:

	std::vector<Wall> m_walls; //vector contains the created walls for the border
	std::vector<sf::Text> m_texts; //vector contains texts of the menu
	sf::Text m_status;
	std::vector<sf::Sprite> m_images; //vector contains images of the menu
	sf::Texture m_logo; //logo texture
	sf::Texture m_iconTexture; //icon texture

	sf::Font m_font; //font used in the menu
	Board &m_board; //board (for drawing functions)

	//creates image
	sf::Sprite createImg(sf::Texture &texture, sf::Vector2f pos) const;

	//creates text
	sf::Text createText(std::string str) const;

	int m_buttonId; //exit or start texts

	bool m_paused; //paused menu

	bool m_showWindow; //show widnow or not

};

