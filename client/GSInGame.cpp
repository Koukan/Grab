#include <sstream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "GSPauseMenu.hpp"
#include "Input.hpp"
#include "ConcreteObject.hpp"
#include "CommandDispatcher.hpp"
#include "ScrollingSprite.hpp"
#include "GameListCommand.hpp"
#include "GameStateManager.hpp"
#include "NetworkModule.hpp"
#include "Rules.hpp"
#include "Map.hpp"
#include "CircleHitBox.hpp"
#include "RendererManager.hpp"

GSInGame::GSInGame(std::list<Player *> const &players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online)
	: GameState("Game"), _idPlayer(0),
	  _players(players), _mode(mode), _map(map), _nbPlayers(nbPlayers), _nbDie(0), _online(online), _scores(4, 0), _scoreFonts(nbPlayers, this->getFont("buttonFont")),
	_nameFonts(nbPlayers, this->getFont("buttonFont")), _rangeBegin(0), _rangeEnd(0),
	_currentId(0), _fire(false), _elapsedTime(0)
{
}

GSInGame::~GSInGame()
{}

void		GSInGame::preload()
{
  this->addGroup("spawners");
  this->addGroup("players", 40);
  this->addGroup("playersOnline", 40);
  this->addGroup("playerShots", 40);
  this->addGroup("grabs", 40);
  this->addGroup("cannons", 42);
  this->addGroup("Wall", 0);
  this->addGroup("walls", 4);
  this->addGroup("breakableWalls", 3);
  this->addGroup("Wall", 0);
  this->addGroup("shot", 9); //what is it ??
  this->addGroup("monster", 10);
  this->addGroup("background2", 2);
  this->addGroup("background3", 3);
  this->addGroup("end", 3);
  this->setCollisionGroups("Wall", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("Wall", "monster", &Rules::wallTouchObject);
  //this->setCollisionGroups("Wall", "walls", &Rules::wallTouchObject);
  this->setCollisionGroups("Wall", "breakableWalls", &Rules::wallTouchObject);
  this->setCollisionGroups("Wall", "playerShots", &Rules::wallTouchObject);
  this->setCollisionGroups("grabs", "monster", &Rules::grabTouchMonster);
  this->setCollisionGroups("grabs", "players", &Rules::grabTouchPlayer);
  this->setCollisionGroups("playerShots", "monster", &Rules::shotTouchMonster);
  this->setCollisionGroups("playerShots", "breakableWalls", &Rules::shotTouchMonster);
  this->setCollisionGroups("walls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("breakableWalls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("invisibleWalls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("shot", "players", &Rules::shotTouchPlayer);
  this->setCollisionGroups("monster", "players", &Rules::shotTouchPlayer);
  this->setCollisionGroups("walls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("walls", "playerShots", &Rules::wallTouchObject);
  this->setCollisionGroups("breakableWalls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("grabs", "invisibleWalls", &Rules::grabTouchWall);

  // load xml
  this->load("resources/map/randomMap.xml");

  //test map
  this->addGameObject(static_cast<Map*>(this->getResource("level1", 5)), "map");


  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -2000, 8000, 1000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, 1000, 8000, 1000)), "Wall");

  int const large = 30;
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, -large + 30,
	  RendererManager::get().getWidth(), large)), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-large + 30, 0,
	  large, RendererManager::get().getHeight())), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, RendererManager::get().getHeight() - 30,
	  RendererManager::get().getWidth(), large)), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(RendererManager::get().getWidth() - 30, 0,
	  large, RendererManager::get().getHeight())), "invisibleWalls");
}

void		GSInGame::registerShipCallbacks()
{
  for (std::list<Player *>::const_iterator it = this->_players.begin(); it != this->_players.end(); ++it)
  {
	  if ((*it)->getType() == Player::KEYBOARD)
	  {
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputUp,
			  static_cast<int>(Core::Keyboard::Up));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputDown,
			  static_cast<int>(Core::Keyboard::Down));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputLeft,
			  static_cast<int>(Core::Keyboard::Left));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputRight,
			  static_cast<int>(Core::Keyboard::Right));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedUp,
			  static_cast<int>(Core::Keyboard::Up));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedDown,
			  static_cast<int>(Core::Keyboard::Down));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedLeft,
			  static_cast<int>(Core::Keyboard::Left));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedRight,
			  static_cast<int>(Core::Keyboard::Right));
		  this->getInput().registerInputCallback((*it)->getAction(Player::PAUSE).Type,
			  *this, &GSInGame::inputEscape,
			  static_cast<int>((*it)->getAction(Player::PAUSE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *(*it)->getShip(), &Ship::inputReleasedSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputGrab1,
			  static_cast<int>((*it)->getAction(Player::GRAB1).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *(*it)->getShip(), &Ship::inputGrab2,
			  static_cast<int>((*it)->getAction(Player::GRAB2).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			 *(*it)->getShip(), &Ship::inputGrab3,
			  static_cast<int>((*it)->getAction(Player::GRAB3).Key.Code));
	  }
	  else
	  {
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickMoved,
			  *(*it)->getShip(), &Ship::inputJoystickMoved, -1, (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::PAUSE).Type,
			  *this, &GSInGame::inputEscape,
			  static_cast<int>((*it)->getAction(Player::PAUSE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonPressed,
			  *(*it)->getShip(), &Ship::inputFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
			  *(*it)->getShip(), &Ship::inputReleasedFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonPressed,
			  *(*it)->getShip(), &Ship::inputSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
			  *(*it)->getShip(), &Ship::inputReleasedSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB1).Type,
			 *(*it)->getShip(), &Ship::inputGrab1,
			  static_cast<int>((*it)->getAction(Player::GRAB1).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB2).Type,
			 *(*it)->getShip(), &Ship::inputGrab2,
			  static_cast<int>((*it)->getAction(Player::GRAB2).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB3).Type,
			 *(*it)->getShip(), &Ship::inputGrab3,
			  static_cast<int>((*it)->getAction(Player::GRAB3).JoystickButton.Button),
			  (*it)->getType() - 1);
	  }
  }
}

void		GSInGame::onStart()
{
  GameState *state = Core::GameStateManager::get().getGameState("Preload");
  if (state)
	state->pause();
  /*ScrollingSprite *obj1 = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::VERTICAL, 0.075);
  obj1->pushSprite("star background");
  this->addGameObject(obj1, "background2");*/

  if (!_online)
      this->createShips();
  this->registerShipCallbacks();
}

void		GSInGame::onEnd()
{
  GameState *state = Core::GameStateManager::get().getGameState("Preload");
  if (state)
	state->play();
}

bool		GSInGame::handleCommand(Core::Command const &command)
{
  static Method<std::string const> const	methods[] = {
	{"score", &GSInGame::score},
	{"move", &GSInGame::move},
	{"rangeid", &GSInGame::rangeid},
	{"spawnspawner", &GSInGame::spawnspawner},
	{"spawndecoration", &GSInGame::spawndecoration},
	{"spawnsound", &GSInGame::spawnsound},
	{"spawnend", &GSInGame::spawnend},
	{"respawnplayer", &GSInGame::respawnplayer}
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

  for (unsigned int i = 0; i < this->_nbPlayers; ++i)
    {
      ss.str("");
      ss << "P" << (i+1);
      this->_nameFonts[i] = this->getFont("buttonFont");
      this->_nameFonts[i]->setText(ss.str());
      this->_nameFonts[i]->setColor(255, 0, 0);
      this->_nameFonts[i]->setPosition((1024 / (this->_nbPlayers + 1)) * (i+1) - this->_nameFonts[i]->getWidth() / 2, 680);
      this->addGameObject(this->_nameFonts[i], "score", 20);
    }

  for (unsigned int i = 0; i < this->_nbPlayers; ++i)
    {
      this->_scoreFonts[i] = this->getFont("buttonFont");
      this->_scoreFonts[i]->setText("0000000");
      this->_scoreFonts[i]->setColor(255, 0, 0);
      this->_scoreFonts[i]->setPosition((1024 / (this->_nbPlayers + 1)) * (i+1) - this->_scoreFonts[i]->getWidth() / 2, 720);
      this->addGameObject(this->_scoreFonts[i], "score", 20);
    }
}

void		GSInGame::playerDie(Player &)
{
	this->_nbDie++;
	if (this->_nbDie == this->_nbPlayers)
		this->gameover();
}

void		GSInGame::gameover()
{
	std::cout << "Game Over !!!" << std::endl;
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
	Core::GameStateManager::get().popState();
}

void		GSInGame::inputEscape(Core::InputCommand const &/*event*/)
{
  if (!_online)
    {
      this->pause(PHYSIC);
    }
  Core::GameStateManager::get().pushState(*(new GSPauseMenu()), Core::GameState::PHYSIC);
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
	obj.setScrollY(event.position);
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


void		GSInGame::spawnend(GameCommand const &event)
{
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, event.y, 1000, 8000)), "end");
}

void		GSInGame::spawnspawner(GameCommand const &event)
{
	Core::BulletCommand		*spawner = new Core::BulletCommand(event.data, *this, 0, 0, event.vx, event.vy);
	this->updatePositions(event, *spawner);
	this->addGameObject(spawner, "spawners");
}

void		GSInGame::spawndecoration(GameCommand const &event)
{
	ConcreteObject			*object = new ConcreteObject(event.data, *(new Core::CircleHitBox(event.x, event.y, 1)), event.vx, event.vy);
	object->setScrollY(event.position);
	this->addGameObject(object, "decorations");
}

void		GSInGame::spawnsound(GameCommand const &event)
{
	Core::Sound	*sound = this->getSound(event.data);
	if (sound)
		sound->play();
}

void		GSInGame::respawnplayer(GameCommand const &event)
{
	event.player->respawn();
}

void		GSInGame::createShips()
{
  // player colors

  static struct {
    int r;
    int g;
    int b;
  } playerColors[] = {
		{255, 0, 0},
		{0, 255, 0},
		{0, 0, 255},
		{255, 255, 0}
	};

  Ship					*ship;
  unsigned int			i = 0;
  for (std::list<Player *>::const_iterator it = _players.begin(); it != _players.end(); ++it, ++i)
    {
		ship = new Ship(**it, *(*it)->getShipInfo(), playerColors[i].r,
				playerColors[i].g, playerColors[i].b);
		ship->setY(600);
		ship->setX(i * 250 + 150);
		this->addGameObject(ship, "players");
    }
}

uint32_t	GSInGame::getNextId()
{
	if (_currentId == _rangeEnd)
	{
		_currentId = _rangeBegin;
	}
	return (_currentId++);
}
