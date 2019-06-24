#include "StageController.h"
#include "Brick.h"
#include "Stone.h"
#include "Bushes.h"
#include "Water.h"
#include "Util.h"

using std::make_unique;


StageController::StageController(SheetsController * sheetsController)
	:m_sheetsController(sheetsController), m_stage(1), m_posId(0)
{
}


bool StageController::loadStage(std::vector<unique_ptr<Object>>& fixedObjects)
{
	m_stageFile.open(STAGES_PATH + std::to_string(m_stage));
	if (!m_stageFile.is_open())
		return false;
	else
	{
		std::vector<std::string> map = loadMap(m_stageFile);
		fixedObjects.clear();

		float y = 25;
		for (size_t i = 0; i < map.size(); i++, y+=16)
		{
			float x = 25;
			for (size_t j = 0; j < map[i].size(); j++, x+=16)
			{
				switch (map[i][j])
				{
				case '#':
					fixedObjects.emplace_back(make_unique<Brick>(sf::Vector2f(x, y)));
					break;

				case '@': 
					fixedObjects.emplace_back(make_unique<Stone>(sf::Vector2f(x, y)));
					break;
				case '~':
					fixedObjects.emplace_back(make_unique<Water>(sf::Vector2f(x, y)));
					break;
				case '%': 
					fixedObjects.emplace_back(make_unique<Bushes>(sf::Vector2f(x, y))); 
					break;
				}
			}
		}
	}
	m_stage++;
	m_stageFile.close();
	return true;
}

int StageController::getStageId()
{
	return m_stage-1;
}

void StageController::restart()
{
	m_posId = 0;
	m_stage = 1;
}

const sf::Vector2f & StageController::getSpawnPos()
{
	m_posId++;
	m_posId = m_posId % 3;

	if (m_posId == 0)
		return ENEMY_POSITION1;
	else if (m_posId == 1)
		return ENEMY_POSITION2;
	else
		return ENEMY_POSITION3;

}

std::vector<std::string> StageController::loadMap(std::ifstream &stageFile)
{
	std::vector<std::string> map;
	std::string inputString;
	while (std::getline(stageFile, inputString))
		map.push_back(inputString);
	return map;
}
