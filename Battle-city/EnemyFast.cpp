#include "EnemyFast.h"




EnemyFast::EnemyFast(const sf::Vector2f & pos)
	:Enemy(pos, sheetsController->fastTank->getSheets(), sheetsController->fastTank->getData(), 1)

{
	m_speed = ENEMY_SPEED * 1.2;
}

void EnemyFast::updateMovement(Tank * player, Basement * basement)
{
	m_target = basement;

	Enemy::updateMovement(player, basement);
}
