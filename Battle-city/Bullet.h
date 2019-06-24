#pragma once
#include "MovableObject.h"
#include "Wall.h"
#include "Basement.h"
class Tank;

class Bullet : public MovableObject
{
public:
	Bullet(const sf::Vector2f & pos, int direction);
	void draw(sf::RenderWindow* window); //draws bullet (it calls for updateBullet function and then Object::draw)
	bool isDestroyed() const; //returns if bullet is destroyed (finished so we erase it)
	void collide(Object* object) override;
	//checks collision of objects with bullet
	void checkCollision(vector<unique_ptr<Object>>& fixedObjects, sf::RectangleShape* gameBoard, Tank *owner, vector<unique_ptr<Tank>> &tanks, vector<unique_ptr<Tank>>::iterator &it1, vector<unique_ptr<Tank>>::iterator &it2, Basement* basement, const sf::Time &dt);

private:
	sf::Time m_time; //timer for bullet movement\aniamtion
	void updateBullet(); //moves bullet\updates explosion animation
	void destroy(); //destroys bullet (it will get the explosion texture rect vector)
	bool m_destroyed; //states if bullet has exploded or not
	int explosionId; //states explosion id (for animation)
	int m_direction; //direction of bullet (UP,DOWN,LEFT,RIGHT)
	float m_speed; //bullet speed
	bool m_friendly; //states if it is a friend bullet or not (to destroy tank or not)

};

