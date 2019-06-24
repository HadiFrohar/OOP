#pragma once
#include "SheetsCfg.h"
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::pair;

class SheetsController
{
public:
	SheetsController();

private:
	friend class GameController;
	friend class Player;
	friend class EnemyBasic;
	friend class EnemyPower;
	friend class EnemyFast;
	friend class EnemyArmor;
	friend class Tank;
	friend class Bullet;

	friend class Basement;
	friend class Brick;
	friend class Stone;
	friend class Bushes;
	friend class Water;

	unique_ptr<SheetsCfg<vector<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>,
		vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>> playerTank; //player tank

	unique_ptr<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>> basicTank; //enemy basic

	unique_ptr<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>> powerTank; //enemy power

	unique_ptr<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>> fastTank; //enemy fast

	unique_ptr<SheetsCfg<vector<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>,
		vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>> armorTank; //enemy armor

	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> tankEffects; //tank effects (such as appearing effect or shiled effect)
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> bullet; //bullet (in all directions)
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> explosion; //explosion effect
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> baseIcon; //basement img (eagle)
	//unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> powerups; //powerups img
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> sidebarIcons; //side bar icons (stage details bar)
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> gameWords; //words images (Battle City, game over)
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> wall; //wall sheets
	unique_ptr<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>> treeWater; //bushes and water sheets

};

