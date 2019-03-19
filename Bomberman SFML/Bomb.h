#pragma once
#include "UnmoveableObject.h"


class Bomb : public UnmoveableObject
{
public:
	Bomb(const sf::Vector2f & pos, const sf::Texture& sheets); //constructor of the bomb

	//checks if bomb has finished (so we remove it from the vector that stores it), this is the main
	//function of the bomb, it has a timer, each half second it will change the size of the bomb,
	//and after 4 seconds it will state as the bomb is destroyed. another function in the controller will
	//call boom function that booms the bomb and states that it is boomed, after half second of this this
	//function will return true.
	bool finished();
	bool isDestroyed(); //checks if the bomb has been destroyed
	void destroy(); //destroys the bomb, states that it is destroyed
	bool isBoomed(); //checks if the bomb has changed to boom state
	//this function will create boom places in the up-left-down-right-center indexes (if possible)
	void boom(std::vector<std::unique_ptr<Object>> &staticObjects); //change bomb to boom state
	
	void setDamaged(); //sets the damaged as true, so it doesn't damage the robot more than once.
	bool damagedRobot(); //rerturns if the bomb has damaged the robot

	//checks if the sprite is in bomb range, (is in boomplace location)
	bool isInRange(sf::Sprite object);

	void draw(sf::RenderWindow& window); //draws the bomb (or boom palces) on the window


private:
	sf::Clock m_clock; //clock, used as bomb timer
	bool m_destroyed; //states bomb is destroyed
	bool m_boomed; //states if bomb has changed to boom state
	bool m_damaged; //states if bomb damaged robot

	 //vector that contains all the places that has boom place, (LEFT,UP,RIGHT,DOWN,CENTER of bomb position)
	std::vector<sf::Vector2f> m_boomPlaces;

	//creates boom place based on position
	sf::Sprite createBoomPlace(sf::Vector2f pos) const;
	sf::Texture m_sheets; //sheets of the game
};

