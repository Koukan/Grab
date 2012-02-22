#include <sstream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "GSPauseMenu.hpp"
#include "Input.hpp"
#include "ConcreteObject.hpp"
#include "CommandDispatcher.hpp"
#include "ScrollingSprite.hpp"
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "Rules.hpp"


GSInGame::GSInGame(int nbPlayers) : GameState("Game", true), _idPlayer(0),
	_nbPlayers(nbPlayers), _scores(4, 0), _scoreFonts(nbPlayers, this->getFont("buttonFont")), 
	_nameFonts(nbPlayers, this->getFont("buttonFont")), _ship(0),  _rangeBegin(0), _rangeEnd(0),
	_currentId(0), _fire(false), _elapsedTime(0)
{
}

GSInGame::~GSInGame()
{}


void		GSInGame::preload()
{
  this->addGroup("players", 40);
  this->addGroup("Wall", 0);
  this->addGroup("shot", 9);
  this->addGroup("monster", 10);
  this->addGroup("background2", 2);
  this->addGroup("background3", 3);
  this->setCollisionGroups("Wall", "shoot", &Rules::wallTouchObject);
  this->setCollisionGroups("Wall", "monster", &Rules::wallTouchObject);

  // load xml
  this->load("resources/intro.xml");
  this->load("resources/player.xml");
  this->load("resources/shots.xml");
  this->load("resources/enemies.xml");
  this->load("resources/destruction.xml");

  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -2000, 8000, 1000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, 1000, 8000, 1000)), "Wall");
}

void		GSInGame::onStart()
{
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputEscape, static_cast<int>(Core::Keyboard::Escape));
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputUp, static_cast<int>(Core::Keyboard::Up));
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputDown, static_cast<int>(Core::Keyboard::Down));
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputLeft, static_cast<int>(Core::Keyboard::Left));
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputRight, static_cast<int>(Core::Keyboard::Right));
  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased, *this, &GSInGame::releaseInputUpDown, static_cast<int>(Core::Keyboard::Up));
  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased, *this, &GSInGame::releaseInputUpDown, static_cast<int>(Core::Keyboard::Down));
  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased, *this, &GSInGame::releaseInputLeftRight, static_cast<int>(Core::Keyboard::Left));
  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased, *this, &GSInGame::releaseInputLeftRight, static_cast<int>(Core::Keyboard::Right));
  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed, *this, &GSInGame::inputSpace, static_cast<int>(Core::Keyboard::Space));
  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased, *this, &GSInGame::releaseInputSpace, static_cast<int>(Core::Keyboard::Space));
  // add gui
  ScrollingSprite *obj1 = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::VERTICAL, 0.075);
  obj1->pushSprite("star background");
  this->addGameObject(obj1, "background2");

  new Ship("player1", "osef", 0, 20, 255, 255, 255, std::make_pair<int, int>(0, 0),
	   std::make_pair<int, int>(2, 2), std::make_pair<int, int>(4, 4), "players");


}

void		GSInGame::update(double elapsedTime)
{
	if (this->_elapsedTime == 0)
	{
		if (this->_ship && this->_fire)
		{
			GameCommand *cmd = new GameCommand("Spawn", this->getNextId(), Resources::SHOOT,
			static_cast<int16_t>(this->_ship->getX()),
			static_cast<int16_t>(this->_ship->getY()),
			0,
			-400);
			this->spawn(*cmd);
			Core::CommandDispatcher::get().pushCommand(*cmd);
			this->_elapsedTime += 500;
		}
	}
	else
	{
		if (this->_elapsedTime - elapsedTime < 0)
			this->_elapsedTime = 0;
		else
			this->_elapsedTime -= elapsedTime;
	}
}

void		GSInGame::onEnd()
{}

bool		GSInGame::handleCommand(Core::Command const &command)
{
  static Method<std::string const> const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"life", &GSInGame::life},
	{"score", &GSInGame::score},
	{"spawn", &GSInGame::spawn},
	{"move", &GSInGame::move},
	{"rangeid", &GSInGame::rangeid}
  };

  for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); ++i)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(static_cast<GameCommand const &>(command));
			return true;
		}
	}
  return (false);
}

void		GSInGame::displayScores()
{
  std::ostringstream	ss;

  for (int i = 0; i < this->_nbPlayers; ++i)
    {
      ss.str("");
      ss << "P" << (i+1);
      this->_nameFonts[i] = this->getFont("buttonFont");
      this->_nameFonts[i]->setText(ss.str());
      this->_nameFonts[i]->setColor(255, 0, 0);
      this->_nameFonts[i]->setPosition((1024 / (this->_nbPlayers + 1)) * (i+1) - this->_nameFonts[i]->getWidth() / 2, 680);
      this->addGameObject(this->_nameFonts[i], "score", 20);
    }

  for (int i = 0; i < this->_nbPlayers; ++i)
    {
      this->_scoreFonts[i] = this->getFont("buttonFont");
      this->_scoreFonts[i]->setText("0000000");
      this->_scoreFonts[i]->setColor(255, 0, 0);
      this->_scoreFonts[i]->setPosition((1024 / (this->_nbPlayers + 1)) * (i+1) - this->_scoreFonts[i]->getWidth() / 2, 720);
      this->addGameObject(this->_scoreFonts[i], "score", 20);
    }  
}

void		GSInGame::inputUp(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVy(-200);
      this->throwShip();
    }
}

void		GSInGame::inputDown(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVy(200);
      this->throwShip();
    }
}

void		GSInGame::inputLeft(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVx(-200);
      this->throwShip();
    }
}

void		GSInGame::inputRight(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVx(200);
      this->throwShip();
    }
}

void		GSInGame::releaseInputUpDown(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVy(0);
      this->throwShip();
    }
}

void		GSInGame::releaseInputLeftRight(Core::InputCommand const &/*event*/)
{
  if (this->_ship)
    {
      this->_ship->setVx(0);
      this->throwShip();
    }
}

void		GSInGame::inputEscape(Core::InputCommand const &/*event*/)
{
  Core::GameStateManager::get().pushState(*(new GSPauseMenu()), Core::GameState::NONE);
}

void		GSInGame::inputSpace(Core::InputCommand const &/*event*/)
{
	this->_fire = true;
}

void		GSInGame::releaseInputSpace(Core::InputCommand const &/*event*/)
{
	this->_fire = false;
}

void		GSInGame::throwShip()
{
  GameCommand *cmd = new GameCommand("Move", this->_ship->getId(), 0,
				     static_cast<int16_t>(this->_ship->getX()),
				     static_cast<int16_t>(this->_ship->getY()),
				     static_cast<int16_t>(this->_ship->getVx()),
				     static_cast<int16_t>(this->_ship->getVy()));

  Core::CommandDispatcher::get().pushCommand(*cmd); //send to network
}

void		GSInGame::spawn(GameCommand const &event)
{
  static Method<Resources::type> const	methods[] = {
    {Resources::P1, &GSInGame::loadP1},
    {Resources::P2, &GSInGame::loadP2},
    {Resources::P3, &GSInGame::loadP3},
    {Resources::P4, &GSInGame::loadP4},
    {Resources::SINGLE_MONSTER, &GSInGame::loadMonster},
    {Resources::BOMB_MONSTER, &GSInGame::loadMonster},
    {Resources::SINUSOIDAL_MONSTER, &GSInGame::loadMonster},
    {Resources::METROID_MONSTER, &GSInGame::loadMonster},
    {Resources::BOSS_METROID, &GSInGame::loadMonster},
    {Resources::RANDOM_MONSTER, &GSInGame::loadMonster},
    {Resources::TRON_MONSTER, &GSInGame::loadMonster},
    {Resources::DEFAULT_SHOT, &GSInGame::loadMonster},
    {Resources::BOSS_SHOT, &GSInGame::loadMonster},
    {Resources::ANIMATED_SHOT, &GSInGame::loadMonster},
    {Resources::SHOT, &GSInGame::loadMonster},
    {Resources::SHOOT, &GSInGame::loadShoot}
  };

  for (size_t i = 0;
       i < sizeof(methods) / sizeof(*methods); i++)
    {
      if (static_cast<Resources::type>(event.idResource) == methods[i].name)
	{
	  (this->*methods[i].method)(event);
	  if (static_cast<uint16_t>(event.idResource) == this->_idPlayer)
	    {
	      this->_ship = static_cast<Core::PhysicObject *>(this->getGameObject(event.idObject));
	    }
	}
    }
}

void		GSInGame::destroy(GameCommand const &event)
{
	Core::GameObject *tmp = this->getGameObject(event.idObject);
	if (tmp)
	{
		if (this->_ship->getId() == event.idObject)
			this->_ship = 0;
		tmp->erase();
	}
}

void		GSInGame::life(GameCommand const &/*event*/)
{
	//actions
}

void		GSInGame::score(GameCommand const &event)
{
	if (event.idObject < 4)
	{
		_scores[event.idObject] = event.score;
	}
}

void		GSInGame::move(GameCommand const &event)
{
	Core::PhysicObject *obj = static_cast<Core::PhysicObject *>(this->getGameObject(event.idObject));

	if (obj)
		this->updatePositions(event, *obj);
}

void		GSInGame::updatePositions(GameCommand const &event, Core::PhysicObject &obj) const
{
	obj.setX(event.x);
	obj.setY(event.y);
	obj.setVx(event.vx);
	obj.setVy(event.vy);
}

void		GSInGame::loadP1(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);
  ConcreteObject *player = new ConcreteObject(this->getSprite("player1"), *hitbox, event.vx, event.vy);
  player->setId(event.idObject);
  this->addGameObject(player, "players");
}

void		GSInGame::loadP2(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);
  ConcreteObject *player = new ConcreteObject(this->getSprite("player2"), *hitbox, event.vx, event.vy);
  player->setId(event.idObject);
  this->addGameObject(player, "players");
}

void		GSInGame::loadP3(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);
  ConcreteObject *player = new ConcreteObject(this->getSprite("player3"), *hitbox, event.vx, event.vy);
  player->setId(event.idObject);
  this->addGameObject(player, "players");
}

void		GSInGame::loadP4(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);
  ConcreteObject *player = new ConcreteObject(this->getSprite("player4"), *hitbox, event.vx, event.vy);
  player->setId(event.idObject);
  this->addGameObject(player, "players");
}

void		GSInGame::loadMonster(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);

  if (event.idResource >= Resources::SINGLE_MONSTER)
  {
  	Core::Sprite *sprite = this->getSprite(Resources::monsters[event.idResource - Resources::SINGLE_MONSTER].sprite);
  	if (sprite)
  	{
		ConcreteObject *monster = new ConcreteObject(sprite, *hitbox, event.vx, event.vy);
		monster->setId(event.idObject);
		this->addGameObject(static_cast<Core::GameObject *>(monster), "monster");
  	}
  }
}

void		GSInGame::loadShoot(GameCommand const &event)
{
  Core::HitBox *hitbox = new Core::RectHitBox(event.x, event.y, 2, 2);
  ConcreteObject *obj = new ConcreteObject(this->getSprite("default shot"), *hitbox, event.vx, event.vy);
  obj->setId(event.idObject);
  this->addGameObject(static_cast<Core::GameObject *>(obj), "shoot");
}

void		GSInGame::rangeid(GameCommand const &event)
{
  this->_rangeBegin = event.idObject;
  this->_rangeEnd = event.idResource;
  this->_currentId = event.idObject;
  this->addGroup("shoot", 8, event.idObject, event.idResource);
  this->_idPlayer = event.x;
  this->displayScores();
  this->_nameFonts[this->_idPlayer]->setText(NetworkModule::get().getName());
  this->_nameFonts[this->_idPlayer]->setPosition((1024 / (this->_nbPlayers + 1)) * (this->_idPlayer+1) - this->_nameFonts[this->_idPlayer]->getWidth() / 2, 680);
  Core::CommandDispatcher::get().pushCommand(*(new GameListCommand("Player", PlayerStatus::READY, NetworkModule::get().getName())));
}

uint32_t	GSInGame::getNextId()
{
	if (_currentId == _rangeEnd)
	{
		_currentId = _rangeBegin;
	}
	return (_currentId++);
}
