#pragma once
#include "Enemy.h"
class EnemyFast : public Enemy
{
public:
	EnemyFast(const sf::Vector2f &pos);

private:
	//target is the basement
	void updateMovement(Tank *player, Basement* basement) override;


};

