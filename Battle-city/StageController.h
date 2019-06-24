#pragma once
#include "SheetsController.h"
#include "Object.h"
#include "Wall.h"
class StageController
{
public:
	StageController(SheetsController* sheetsController);

	//opens stage file (if exist) loads stage and returns true, otherwise it returns false (means all stages are done)
	bool loadStage(std::vector<unique_ptr<Object>>& fixedObjects);
	
	int getStageId(); //returns stage number
	void restart(); //restarts the controller (so we start from the first stage)

	const sf::Vector2f &getSpawnPos(); //returns next enemy to spawn position

private:
	static std::vector<std::string> loadMap(std::ifstream &stageFile); //loads map from file
	std::ifstream m_stageFile; //stage file
	SheetsController* m_sheetsController; //game sheets controller
	int m_stage, //stage number
		m_posId; //next enemy to spawn
};

