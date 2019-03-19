#include <vector>
#include <string>
#include <iostream>
#include "screen.h"
#include "Keyboard.h"
#include <fstream>
#include"Board.h"
#include "Settings.h"

//Game function is the main function, reads the maps(levels) and creates the
//board for a specfic level
void game();

int main(){

	game();

	return EXIT_SUCCESS;
}



void game()
{

	//opens the file and check if its opened
	std::ifstream file("Board.txt");
	if (!file)
	{
		perror("Couldn't open file");
		exit(EXIT_FAILURE);
	}

	std::string inputString; //help string: we get the lines of the file using it
	std::vector<std::string> map; //after reading an level we put it in this vector
	Robot robot; //player robot
	int size, //size of the map
		steps; //steps of the level

	//In this loop we keep reading the file till we reach EOF,
	//that means the game has finished
	while (getline(file, inputString))
	{
		//this loop to skip the empty lines in the file.
		while (inputString.empty())
			getline(file, inputString);

		//clear the map (if the vector has a previous map)
		map.clear();
		getSettings(inputString, size, steps); //get the size and the steps

		//read the map till we reach line number=size
		//we add it to the vector
		for (int i = 0; i < size; i++)
		{
			getline(file, inputString);
			map.push_back(inputString);
		}

		//clear the screen (if the screen had the previous level)
		system("cls");

		//create the board
		Board board;
		board.setRobot(robot); //send the robot to the board
		board.setSettings(map, size, steps);
		//board.setMap(map); //send the map to the board
		//board.setSize(size); //send map size
		//board.setSteps(steps); //send steps of the level
		
		//in this loop we keep replaying the level if the robot lost the level (
		//used all steps) and still has life
		while (!board.finishLevel() && robot.getLife() > 0)
		{
			board.clear(); //we clear the guards, bombs and etc..
			robot = board.getRobot(); //get status of robot after losing level
			board.setRobot(robot); //send the updated robot to the board
			
			board.setSettings(map, size, steps);
			//board.setMap(map); //send the map to the board
			//board.setSize(size); //send map size
			//board.setSteps(steps); //send steps of the level
		}

		//if he finished the map or died,  we update the robot
		robot = board.getRobot();

		//if he died then he loses, so no need to continue on other maps (if there)
		if (robot.getLife() == 0)
			break;
	}

	file.close();

	moveCursor({ (short)size + 1, 0 });
}

