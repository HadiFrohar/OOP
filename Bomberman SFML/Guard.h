#pragma once
#include "MoveableObject.h"
#include "Robot.h"

class Guard : public MoveableObject
{
public:
	Guard(const sf::Vector2f & pos, const sf::Texture& sheets); //guard constructor

	//moves the guard, the move is based on robot position, it has 4 different types: left up down right or no move
	void move(std::vector<std::unique_ptr<Object>> &staticObjects, Robot &robot, Door &door, int i);

	void isInRobotRange(Robot &robot); //checks if in robot range and damages him if yes

private:
	static constexpr float SPEED = (float)GUARDSPEED; //movment speed

	void moveLeft() override; //moves left (if possible) and it will change movement direction
	void moveRight() override; //moves right (if possible) and it will change movement direction
	void moveDown() override; //moves down (if possible) and it will change movement direction
	void moveUp() override; //moves up (if possible) and it will change movement direction

	//it will update the position of the image in the sheets based on movement direction (or noMove)
	void updateAnimation() override;

	bool noMove; //true if the guard didn't move


};
