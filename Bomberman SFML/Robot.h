#pragma once
#include "MoveableObject.h"
#include "Door.h"



class Robot : public MoveableObject
{
public:
	Robot(); //robot constructor

	void clear(); //clears the robot, new position will be (0,0)
	void resetScore(); //resets the score to be 0
	void setStartLife(); //sets life of the robot to be as start life

	//moves the robot (also place bomb if needed), it will check if the robot can move to a specific place
	//if the map is big it will move the view
	void move(std::vector<std::unique_ptr<Object>> &staticObjects, std::vector<Bomb> &bombs, sf::View &view, int mapSize);

	bool isUp(sf::Vector2f &pos); //checks if robot position is up
	bool isRight(sf::Vector2f &pos); //checks if robot position is down

	void damage(); //decreases 1 from robot life
	int getLife(); //returns robot life

	bool isInProtection(); //checks if robot is in protection from damage

	int getScore(); //returns robot score
	void addScore(int score); //adds score to the robot

	bool win(Door door); //returns true if the robot is on door block (win)
	bool isAlive(); //checks if the robot still alive

	void setBombs(int bombs); //sets number of bombs that the robot has for level
	int getBombs(); //gets number of the bomb that the robot has



private:
	static constexpr float SPEED = (float)ROBOTSPEED; //robot speed
	unsigned int m_life; //robot life
	unsigned int m_score; //robot score
	bool m_inDamage; //checks if the robot was damaged in the last 3 seconds
	int m_bombs;

	void placeBomb(std::vector<Bomb> &bombs);
	void moveLeft() override; //moves left (if possible) and it will change movement direction
	void moveRight() override; //moves right (if possible) and it will change movement direction
	void moveDown() override; //moves down (if possible) and it will change movement direction
	void moveUp() override; //moves up (if possible) and it will change movement direction

	//it will update the position of the image in the sheets based on movement direction
	virtual void updateAnimation() override;

	//timer for the damage protection, we use it because we don't want to keep damaging the player (every ms lets
	//say) and so the robot can run when getting an damage
	sf::Clock m_damageClock;
};

