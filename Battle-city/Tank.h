#pragma once
#include "MovableObject.h"
#include "Util.h"
#include "Bullet.h"
class Tank : public MovableObject
{
public:
	Tank(const sf::Vector2f & pos, const sf::Texture & texture, vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>& intRects, int direction, int armor);
	virtual ~Tank() = 0 {};

	//draws tank (if alive), appearing effect (if didn't start playing yet). and draws\updates tank bullets
	virtual void draw(sf::RenderWindow* window) override;

	//moves tank based on the movement (which the derived class) did. checks if movment is possible, or on water
	virtual	void move(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement, const sf::Time &dt);
	virtual void restart(); //restarts tank: clears tank bullets, adjusts tank position, sets it as in appearing effect
	void collide(Object* object) override; //calls object.collideWith(this)
	void collideWith(Bullet* bullet) override; //collision with bullet effect: calls for damage function
	void collideWith(Wall* wall) override; //collision with wall effect: tank cant move
	void collideWith(Water* water) override; //collision with water effect: tank is moving slow
	void collideWith(Basement* basement) override; //collision with basement effect: tank cant move (possible to add life for player, once in a specific time. or rank)
	bool isAlive(); //returns if tank is alive (on screen)
	bool isBoomed(); //returns if tank is boomed (in explosion)

	const sf::Vector2f & getTankPos() const; //returns tank position

	void checkCollisionWithBullets(Bullet* bullet); //checks bullets collision (two bullets collide)


protected:
	void slowMovement(); //makes tank move slowly (slowMovement=true, in the move function if it is true it will move half movement)
	virtual void damage(); //damages tank
	void newBullet(); //adds new bullet to tank container based on tank direction
	
	//checks tank bullet, if bullet is finished then it will remove it, otherwise it will check collision of objects with bullet
	void checkBullets(vector<unique_ptr<Object>>& walls, sf::RectangleShape* gameBoard, vector<unique_ptr<Tank>> &tanks, std::vector<unique_ptr<Tank>>::iterator &it1, std::vector<unique_ptr<Tank>>::iterator &it2, Basement* basement, const sf::Time &dt);

	sf::Time m_lifeTime; //states tank life time, explosion time

	sf::Time m_animationTime; //for movement animation 
	sf::Time m_animationPassedTime; //time sice last movement animation, so frames don't change every time

	sf::Time m_bulletTime; //for bullets (one bullet in time)
	sf::Time m_bulletPassedTime; //time since last bullet, so tanks don't throw bullets all the time

	float m_speed; //tank speed

	int m_direction; //tank direction

	bool m_appearingEffect; //tank is in appearing effect

	void updateAnimation(int direction); //updates tank animation, it gets direction, updates tank direction (if needed), and if possible it animates tank

	//returns vector of movement to move (based on direction)
	sf::Vector2f leftMovement(const float &dt);
	sf::Vector2f rightMovement(const float &dt);
	sf::Vector2f upMovement(const float &dt);
	sf::Vector2f downMovement(const float &dt);

	//tank sheets info (IntRects)
	vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>> m_intRects;

	void resetSprite(); //resets texture, intRects (we call for this after effects like appearing efect)

	bool m_destroyed; //states if tank is destroyed
	int m_effectId; //effect id

	void boomEffect(); //animates explosion

	virtual void updateTime(const sf::Time &dt); //updates passed_times

	virtual void destroy(); //destroys tank

	sf::Vector2f m_pos; //tank start position
	int m_armor; //tank armor
	bool m_slowMovement, //states if tank moves slow (on water)
		m_canMove; //states if tank can move the last movement

	sf::Vector2f m_movement;

private:
	void appearEffect(); //animates appearing effect
	void checkMovement(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, std::vector<unique_ptr<Tank>> &tanks, Basement* basement);

	vector<unique_ptr<Bullet>> m_bullets; //tank bullets
	sf::Texture m_tankTexture; //tank texture


};

