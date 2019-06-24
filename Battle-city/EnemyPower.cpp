#include "EnemyPower.h"




EnemyPower::EnemyPower(const sf::Vector2f & pos)
	:Enemy(pos, sheetsController->powerTank->getSheets(), sheetsController->powerTank->getData(), 1)
{
	m_tankPower = 500;
}

void EnemyPower::updateMovement(Tank * player, Basement * basement)
{
	m_target = player;

	Enemy::updateMovement(player, basement);
}
