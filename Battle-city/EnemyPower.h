#pragma once
#include "Enemy.h"
class EnemyPower : public Enemy
{
public:
	EnemyPower(const sf::Vector2f & pos);
private:
	//target is the player
	void updateMovement(Tank *player, Basement* basement) override;

};

