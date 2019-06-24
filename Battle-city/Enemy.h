#pragma once
#include "Tank.h"
class Enemy : public Tank
{
public:
	Enemy(const sf::Vector2f & pos, const sf::Texture & texture, vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>& intRects, int life);
	void move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement, const sf::Time &dt) override;
	void draw(sf::RenderWindow* window) override;

protected:
	void updateTime(const sf::Time &dt) override; //updates times
	sf::Time m_targetTime, m_pTargetTime; //for target choosing
	sf::Time m_pMovementTime; //passed time since last choosing movement
	sf::Time m_movementTime; //movement time
	void resetMovementTime(); //randomize time to keep an movement
	void updateDirection(); //updates direction bassed on target
	void updateTarget(Tank *player, Basement* basement); //updates target to the closer
	float distance(const Object *otherObject); //distance between two objects
	Object * m_target; //target
	int m_tankPower; //tank power: timer between bullets
	virtual void updateMovement(Tank *player, Basement* basement); //updates tank movement 

private:
	sf::Vector2f getMovement(const sf::Time &dt); //returns tank movement
	void updateBullets(); //adds new bullet to tank
};

