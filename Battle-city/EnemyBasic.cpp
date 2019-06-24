#include "EnemyBasic.h"


EnemyBasic::EnemyBasic(const sf::Vector2f & pos)
	:Enemy(pos, sheetsController->basicTank->getSheets(), sheetsController->basicTank->getData(), 1)

{
	m_speed = ENEMY_SPEED;
}

void EnemyBasic::updateMovement(Tank * player, Basement * basement)
{

	if (m_pTargetTime > m_targetTime)
		updateTarget(player, basement);

	Enemy::updateMovement(player, basement);

}

