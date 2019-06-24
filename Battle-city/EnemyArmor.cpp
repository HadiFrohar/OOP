#include "EnemyArmor.h"





EnemyArmor::EnemyArmor(const sf::Vector2f & pos)
	:Enemy(pos, sheetsController->armorTank->getSheets(), sheetsController->armorTank->getData()[0], 3)
{
}

void EnemyArmor::updateMovement(Tank * player, Basement * basement)
{
	if (m_pTargetTime > m_targetTime)
		updateTarget(player, basement);


	Enemy::updateMovement(player, basement);
}
