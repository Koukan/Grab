#include <iostream>
#include "Game.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "CircleHitBox.hpp"
#include "CommandDispatcher.hpp"
#include "ServerResourceManager.hpp"
#include "BCommand.hpp"
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
	//this->setCollisionGroups("playerfires", "ship", &Rules::shotTouchMonster);
	//this->setCollisionGroups("shot", "players", &Rules::shotTouchClient);
	//this->setCollisionGroups("ship", "players", &Rules::shotTouchClient);
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
		GameCommand *answer = new GameCommand("Move");
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
		BCommand	*bullet = new BCommand(gc.data, *this, 1100, gc.x, 0, 0);
		this->addGameObject(bullet);
		GameCommand *answer = new GameCommand("Spawn");
		answer->idResource = bullet->getId();
		answer->idObject = this->getBulletParser(gc.data)->getResourceId();
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->client = gc.client;
		Core::CommandDispatcher::get().pushCommand(*answer);
	}
	return false;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}

void		GameLogic::startGame()
{
	this->addGameObject(static_cast<Map*>(this->getResource("level1", 5)));
	this->_gameStarted = true;
}

void GameLogic::createEnnemies(double elapseTime)
{
	static Salvo const salvos[] = {
		{SIMPLE, 5, "single", 1000},
		{SINUSOIDAL, 4, "sinusoidal", 1000},
		{BOMB, 1, "bomb", 1000},
		{RANDOM, 5, "random", 1000},
		{WALL, 1, "wall", 1000}
	};

	static Boss const bosses[] = {
		{"bossMetroid", 10}
	};

	int const salvoFrequency = 10000;
	int const maxSalvos = 10;

	static int i = 0;
	static int y = 0;
	static int nbSalvos = 11;

	if (this->_elapseTime == 0)
	{
		if (nbSalvos > maxSalvos)
		{
			int j = rand() % (sizeof(bosses) / sizeof(*bosses));
			this->addGameObject(new BCommand(bosses[j].bulletName, *this, 1100, 400, 0, 0));
			nbSalvos = 0;
			this->_elapseTime = 10000;
		}
		else if (this->_nbEnemies == 0)
		{
			i = rand() % (sizeof(salvos) / sizeof(*salvos));
			y = rand() % 700;
			this->_nbEnemies = salvos[i].nbEnemies;
			this->_elapseTime = salvoFrequency;
			++nbSalvos;
		}
		else
		{
		  if (salvos[i].bulletName == "bomb")
		    this->addGameObject(new BCommand(salvos[i].bulletName, *this, 1200, -20, 0, 0));
		  else
		    this->addGameObject(new BCommand(salvos[i].bulletName, *this, 1200, y + 34, 0, 0));
			this->_elapseTime += salvos[i].occurenceFrequency;
			--this->_nbEnemies;
		}
	}
	else
	{
		if (this->_elapseTime - elapseTime < 0)
			this->_elapseTime = 0;
		else
			this->_elapseTime -= elapseTime;
	}
}
