#pragma once
#include "Enemy.h"
class EnemyBasic : public Enemy
{
public:
	EnemyBasic(const sf::Vector2f & pos);

private:
	//updates target (if time passed) to the closer target
	void updateMovement(Tank *player, Basement* basement) override;
};

