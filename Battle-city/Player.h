#pragma once
#include "Tank.h"
#include "Wall.h"
class Player : public Tank
{
public:
	Player(const sf::Vector2f & pos= sf::Vector2f(153, 403));

	//moves player, it updates times, checks tank bullets, and moves player (based on his input)
	void move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement, const sf::Time &dt) override;
	
	void draw(sf::RenderWindow* window) override; //draws explosion or it draws tank, draws shield effect (if player is on shield)
	void damage() override; //damages tank (if not on shiled)
	int getLife() const; //returns player life

	void newGame(); //resets player, (reset tank power and life)
	//void killedEnemy();

protected:
	void destroy() override; //destroys tank

private:
	bool m_onShield; //states if player is on shield
	void shieldEffect(); //shiled animation
	//void newRank(); //new rank for player (stronger tank)
	int m_life; //returns player life
	//int m_rank, m_kills; //each 5 kills = new rank
};

