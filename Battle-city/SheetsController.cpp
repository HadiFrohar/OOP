#include "SheetsController.h"
#include "Util.h"

using std::make_unique;

SheetsController::SheetsController()
	:playerTank(make_unique<SheetsCfg<vector<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>,
		vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>>(PLAYER_TANK_CFGPATH)),
	basicTank(make_unique<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>(BASIC_TANK_CFGPATH)),
	powerTank(make_unique<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>(POWER_TANK_CFGPATH)),
	fastTank(make_unique<SheetsCfg<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>,
		pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>(FAST_TANK_CFGPATH)),
	armorTank(make_unique<SheetsCfg<vector<vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>,
		vector<pair<shared_ptr<sf::IntRect>, shared_ptr<sf::IntRect>>>>>(ARMOR_TANK_CFGPATH)),
	tankEffects(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(TANK_EFFECTS_CFGPATH)),
	bullet(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(BULLET_CFGPATH)),
	explosion(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(EXPLOSION_CFGPATH)),
	baseIcon(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(BASE_ICON_CFGPATH)),
//	powerups(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(POWERUPS_CFGPATH)),
	sidebarIcons(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(SIDEBAR_ICONS_CFGPATH)),
	gameWords(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(GAME_WORDS_CFGPATH)),
	wall(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(WALL_CFGPATH)),
	treeWater(make_unique<SheetsCfg<vector<shared_ptr<sf::IntRect>>, shared_ptr<sf::IntRect>>>(TREE_WATER_CFGPATH))
{
}

