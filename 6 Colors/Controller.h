#pragma once
#include "Board.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "Settings.h"
#include "ColorRectangle.h"
#include "ShapesController.h"
#include "User.h"
#include "Computer.h"
#include <memory>

class Controller
{
public:
	Controller();
	//runs the game, we stay in loop till anyone finish, or close\exit\restart game
	void run();

private:
	void createGame(); //creates game
	void createGameButtons(); //create game buttons (color buttons, exit, restart)
	void restartGame(); //restarts game, it clears the shapes, nearby map, players shapes, players score
	void createPlayersTexts(); //creates players score texts
	void checkStartUsedColors(); //disable first colors in game

	void HandleEvents(); //handles events, (windows is closed, or mouse clicked)
	void draw(); //clears the board and draws the shapes,buttons,texts on it

	//we get here when we there is a mouse click, it checks if the user clicked on any game button (restart, exit)
	//and if its user turn it checks if he clicked on color button and plays (if he clicked),
	//then the turn will be for the computer
	void mouseClick(const sf::Vector2f &pos);

	//gives computer to play, it gets a vector that has the count of shapes nearby to computer of every color
	//sorted in descending order, and checks if the color of the biggest color is playable, if yes it will
	//paly with this color, otherwise it will check the next biggest color count, till it can play.
	void computerTurn();

	//board :it has the SFML window and all other resources
	std::unique_ptr<Board> m_board;

	//shapes controller: it has the shapes, creates them
	std::unique_ptr<ShapesController> m_shapeController;

	//color controller it has game colors and everything about colors
	std::shared_ptr<ColorController> m_colorController;

	std::unique_ptr<User> m_user; //user object
	std::unique_ptr<Computer> m_computer; //computer object

	std::vector<ColorRectangle> m_colorButtons; //colors buttons: the colors that the user can\'t play

	std::vector<std::unique_ptr<sf::Text>> m_gameButtons; //exit, restart buttons

	bool m_userToPlay, //states if the turn for the user or not (for computer)
		m_gameFinished, //states if the game has finished
		m_gameRestart; //states if the user requsted to restart the game
};

