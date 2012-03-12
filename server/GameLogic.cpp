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

GameLogic::GameLogic(Game &game)
  : Core::GameState("GameLogic"), _game(game), _nbEnemies(0), _elapseTime(0), _gameStarted(false)
{
	this->load("resources/map/map1.xml");
	this->addGroup("Wall", 0);
	this->addGroup("playerfires", 0);
	this->addGroup("cannons", 0);
	this->addGroup("ship", 0);
	this->addGroup("shot", 0);

	this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(3000, -2000, 1000, 8000)), "Wall");
	this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, -2000, 1000, 8000)), "Wall");
	this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-3000, -2000, 8000, 1000)), "Wall");
	this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-3000, 1000, 8000, 1000)), "Wall");

	this->setCollisionGroups("Wall", "shot", &Rules::wallTouchObject);
	this->setCollisionGroups("Wall", "ship", &Rules::wallTouchObject);
	this->setCollisionGroups("Wall", "playerfires", &Rules::wallTouchObject);
	this->setCollisionGroups("playerShots", "monster", &Rules::shotTouchMonster);
	this->setCollisionGroups("shoot", "players", &Rules::shotTouchClient);
	//this->setCollisionGroups("ship", "players", &Rules::shotTouchClient);
	this->_rand.seed(rand());
}

GameLogic::~GameLogic()
{
}

void		GameLogic::update(double elapseTime)
{
	this->handle(elapseTime);
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
			{"fireState", &GameLogic::fireStateCommand}
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
	this->addGameObject(static_cast<Map*>(this->getResource("level1", 5)), "map");
	this->_gameStarted = true;
	this->setBeginId(10000);
}

uint32_t	GameLogic::getSeed() const
{
	return this->_rand.getSeed();
}

void		GameLogic::spawnSpawnerCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);
	Core::BulletCommand	*bullet = new Core::BulletCommand(gc.data, *this, 1100, gc.x, 0, 0);
	this->addGameObject(bullet);
}

void		GameLogic::moveCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = reinterpret_cast<Player*>(gc.client)->getShip();
	ship->setX(gc.x);
	ship->setY(gc.y);
	ship->setVx(gc.vx);
	ship->setVy(gc.vy);
	GameCommand *answer = new GameCommand("MovePacket");
	answer->idObject = ship->getId();
	answer->x = gc.x;
	answer->y = gc.y;
	answer->vx = gc.vx;
	answer->vy = gc.vy;
	answer->game = &_game;
	answer->client = &reinterpret_cast<Player*>(gc.client)->getClient();
	Core::CommandDispatcher::get().pushCommand(*answer);
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
		std::cout << "releaseCannon" << std::endl;
	}
	else
	{
		ship->addCannon(new Cannon(gc.name, *ship, *this, "", "cannons", "playerShots",
							gc.x, gc.y), gc.idResource);
		std::cout << "addCannon" << std::endl;
	}
}

void		GameLogic::fireStateCommand(Core::Command const &command)
{
	GameCommand const	&gc = static_cast<GameCommand const &>(command);

	Ship	*ship = static_cast<Ship*>(this->getGameObject(gc.idObject));
	if (!ship)
		return ;
	if (gc.idResource == 0)
		ship->releaseFire();
	else if (gc.idResource == 1)
		ship->fire(*this);
	else if (gc.idResource == 2)
		ship->specialFire(*this);
	else if (gc.idResource == 3)
		ship->releaseSpecialFire();
	std::cout << "fireStateCommand " << gc.idResource << std::endl;
}
