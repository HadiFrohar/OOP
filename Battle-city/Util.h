#pragma once
#include <string>
using std::string;

enum DIRECTION { LEFT, RIGHT, UP, DOWN, NOMOVE }; //movement direction
enum MOVEMENT { SLOW, NORMAL, FAST }; //movement speed

const unsigned int GAMEBOARD_SIZE = 416; //(32*13)
const int START_LIFE = 3; //player start life
const float PLAYER_SPEED = 150.0f;
const sf::Vector2f PLAYER_POSITION = sf::Vector2f(153, 403);
const sf::Vector2f ENEMY_POSITION1 = sf::Vector2f(25, 25);
const sf::Vector2f ENEMY_POSITION2 = sf::Vector2f(217, 25);
const sf::Vector2f ENEMY_POSITION3 = sf::Vector2f(409, 25);

const int ENEMIES_COUNT = 20; //enemies count in each stage
const float ENEMY_SPEED = 120.0f;

//game configuration paths
const string PLAYER_TANK_CFGPATH = "rc/player_tank.cfg";
const string BASIC_TANK_CFGPATH = "rc/basic_tank.cfg";
const string POWER_TANK_CFGPATH = "rc/power_tank.cfg";
const string FAST_TANK_CFGPATH = "rc/fast_tank.cfg";
const string ARMOR_TANK_CFGPATH = "rc/armor_tank.cfg";
const string TANK_EFFECTS_CFGPATH = "rc/tank_effects.cfg";
const string BULLET_CFGPATH = "rc/bullet.cfg";
const string EXPLOSION_CFGPATH = "rc/explosion.cfg";
const string BASE_ICON_CFGPATH = "rc/base_icon.cfg";
const string POWERUPS_CFGPATH = "rc/powerups.cfg";
const string SIDEBAR_ICONS_CFGPATH = "rc/sidebar_icons.cfg";
const string GAME_WORDS_CFGPATH = "rc/game_words.cfg";
const string WALL_CFGPATH = "rc/wall.cfg";
const string TREE_WATER_CFGPATH = "rc/tree_water.cfg";
const string PRSTARTK = "rc/fonts/prstartk.ttf";
const string STAGES_PATH = "rc/stages/";

//map characters
const char BRICK = '#';
const char STONE = '@';
const char BUSHES = '%';
const char WATER = '~';

//game colors
const sf::Color GREY = sf::Color(128, 128, 128);