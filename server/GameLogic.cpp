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

GameLogic::GameLogic(Game &game)
  : Core::GameState("GameLogic"), _game(game), _nbEnemies(0), _elapseTime(0), _gameStarted(false)
{
	this->load("resources/map/map1.xml");
	this->addGroup("Wall", 0);
	this->addGroup("playerfires", 0);
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
	GameCommand	const &gc = static_cast<GameCommand const &>(command);
	if (gc.name == "move")
	{
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
		return true;
	}
	else if (gc.name == "spawn")
	{
	  	Core::CircleHitBox		*hitbox = new Core::CircleHitBox(gc.x, gc.y, 15);
	  	Core::Bullet			*bullet = new Core::Bullet(*hitbox, gc.vx, gc.vy);
		bullet->setId(gc.idObject);
		this->addGameObject(bullet, "playerfires", 9);
		GameCommand *answer = new GameCommand("Spawn");
		answer->idResource = gc.idResource;
		answer->idObject = gc.idObject;
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->client = gc.client;
		Core::CommandDispatcher::get().pushCommand(*answer);
		return true;
	}
	else if (gc.name == "spawnspawner")
	{
		Core::BulletCommand	*bullet = new Core::BulletCommand(gc.data, *this, 1100, gc.x, 0, 0);
		this->addGameObject(bullet);
		//GameCommand *answer = new GameCommand("Spawn");
		//answer->idResource = bullet->getId();
		//answer->idObject = this->getBulletParser(gc.data)->getResourceId();
		//answer->x = gc.x;
		//answer->y = gc.y;
		//answer->vx = gc.vx;
		//answer->vy = gc.vy;
		//answer->game = &_game;
		//answer->client = gc.client;
		//Core::CommandDispatcher::get().pushCommand(*answer);
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
