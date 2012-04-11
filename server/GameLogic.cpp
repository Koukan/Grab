#include <iostream>
#include "Game.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"
#include "BulletCommand.hpp"
#include "CircleHitBox.hpp"
#include "CommandDispatcher.hpp"
#include "Rules.hpp"
#include "Map.hpp"
#include "Cannon.hpp"
#include "MonsterGenerator.hpp"

GameLogic::GameLogic(Game &game, const std::string &map)
  : Core::GameState("GameLogic"), _game(game), _nbEnemies(0), _elapseTime(0), _gameStarted(false), _map(0)
{
  this->addGroup("spawners", 0);
  this->addGroup("players", 40);
  this->addGroup("playerShots", 40);
  this->addGroup("grabs", 40);
  this->addGroup("cannons", 42);
  this->addGroup("Wall", 0);
  this->addGroup("walls", 4);
  this->addGroup("breakableWalls", 3);
  this->addGroup("deadlyWalls", 5);
  this->addGroup("shot", 9); // monster shot
  this->addGroup("monster", 10);
  this->addGroup("monster2", 8);
  this->addGroup("trigger", 5);
  this->addGroup("background", 2);
  this->addGroup("starobjects", 3);
  this->addGroup("impacts", 43);
  this->addGroup("scoreBonus", 42);
  this->addGroup("map", 0);
  this->addGroup("traversableWalls", 5);
  this->addGroup("wallShot", 9);
  this->addGroup("shields", 40);
  this->addGroup("blackHoles", 3);
  this->addGroup("blackHoleEnd", 3);
  this->addGroup("particles", 3);
  this->addGroup("playerAuras", 3);

	this->load(map);
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -1000, 4000, 980)), "shotWall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -2000, 8000, 1000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, 1500, 8000, 1000)), "Wall");



  	this->setCollisionGroups("Wall", "shot", &Rules::wallTouchObject);
	this->setCollisionGroups("Wall", "playerShots", &Rules::wallTouchObject);
	this->setCollisionGroups("Wall", "monster", &Rules::wallTouchObject);
	this->setCollisionGroups("walls", "playerShots", &Rules::wallTouchObject);
	this->setCollisionGroups("playerShots", "monster", &Rules::shotTouchMonster);
  	this->setCollisionGroups("playerShots", "monster2", &Rules::shotTouchMonster);
  	this->setCollisionGroups("playerShots", "breakableWalls", &Rules::shotTouchMonster);
	//this->setCollisionGroups("shoot", "players", &Rules::shotTouchClient);
	//this->setCollisionGroups("ship", "players", &Rules::shotTouchClient);
	this->_rand.seed(rand());
}

GameLogic::~GameLogic()
{
}

void		GameLogic::update(double elapseTime)
{
	this->handle(elapseTime);
	this->_elapseTime += elapseTime;
	if (this->_elapseTime > 1000)
	{
		if (_map)
		{
			GameCommand		*command = new GameCommand("MovePacket");
			command->idObject = _map->getId();
			command->x = _map->getX();
			command->y = _map->getY();
			command->vx = _map->getVx();
			command->vy = _map->getVy();
			command->game = &this->_game;
			Core::CommandDispatcher::get().pushCommand(*command);
		}
		this->_elapseTime -= 1000;
	}
	//if (_gameStarted)
	//{
			//this->createEnnemies(elapseTime);
			//}
}

bool		GameLogic::handleCommand(Core::Command const &command)
{
	struct {
		std::string		name;
		void			(GameLogic::*func)(Core::Command const &);
	}	tab[] = {
			{"move", &GameLogic::moveCommand},
			{"spawnspawner", &GameLogic::spawnSpawnerCommand},
			{"updateCannon", &GameLogic::updateCannonCommand},
			{"fireState", &GameLogic::fireStateCommand},
			{"killPlayer", &GameLogic::killPlayerCommand},
			{"decreasePaused", &GameLogic::decreasePaused},
			{"increasePaused", &GameLogic::increasePaused},
			{"bonus", &GameLogic::bonusCommand}
	};

	for (size_t i = 0; i < sizeof(tab) / sizeof(*tab); i++)
	{
		if (command.name == tab[i].name)
		{
			(this->*(tab[i].func))(command);
			return true;
		}
	}
	return false;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}

void		GameLogic::startGame()
{
	this->_map = static_cast<Map*>(this->getResource(this->_game._map, 5));
	MonsterGenerator	*generator = dynamic_cast<MonsterGenerator*>(this->_map);
	if (generator)
		generator->setSeed(this->_rand());
	this->addGameObject(this->_map, "map");
	this->_gameStarted = true;
}

uint32_t	GameLogic::getSeed() const
{
	return this->_rand.getSeed();
}

void		GameLogic::spawnSpawnerCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);
	Core::BulletCommand	*bullet = new Core::BulletCommand(gc.data, *this, gc.x, gc.y, gc.vx, gc.vy, gc.boolean);
	bullet->setSeed(this->_rand());
	bullet->setScrollY(gc.position);
	bullet->setRank(this->_game.nbPlayers());
	this->addGameObject(bullet, "spawners");
}

void		GameLogic::moveCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = gc.player->getShip();
	ship->setX(gc.x);
	ship->setY(gc.y);
	//ship->setVx(gc.vx);
	//ship->setVy(gc.vy);
}

void		GameLogic::updateCannonCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = static_cast<Ship*>(this->getGameObject(gc.idObject));
	if (!ship)
		return ;
	if (gc.data.empty())
	{
		ship->releaseCannon(gc.idResource);
	}
	else
	{
		ship->addCannon(new Cannon(gc.data, *ship, *this, "weapon", "cannons", "playerShots",
							gc.x, gc.y), gc.idResource);
	}
}

void		GameLogic::fireStateCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = static_cast<Ship*>(this->getGameObject(gc.idObject));
	if (!ship && !ship->isGood(gc.score))
		return ;
	if (gc.idResource == 0)
		ship->releaseFire();
	else if (gc.idResource == 1)
		ship->fire();
	else if (gc.idResource == 2)
		ship->specialFire();
	else if (gc.idResource == 3)
		ship->releaseSpecialFire();
}

void		GameLogic::killPlayerCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = static_cast<Ship*>(this->getGameObject(gc.idObject));
	if (ship)
		ship->setDead(gc.boolean, false);
}

void		GameLogic::decreasePaused(Core::Command const &)
{
	this->_map->decreasePaused();
}

void		GameLogic::increasePaused(Core::Command const &)
{
	this->_map->increasePaused();
}

void		GameLogic::bonusCommand(Core::Command const &command)
{	
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = static_cast<Ship*>(this->getGameObject(gc.idObject));
	if (!ship)
		return ;
	ship->specialPower();
}
