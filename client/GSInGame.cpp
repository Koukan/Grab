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
#include "CircleHitBox.hpp"
#include "RendererManager.hpp"
#include "Modes.hpp"
#include "DestroyCommand.hpp"
#include "Cannon.hpp"
#include "GSGameOver.hpp"
#include "GSContinue.hpp"
#include "MonsterGenerator.hpp"
#include "Color.hpp"
#include "ScoreBonus.hpp"
#include "GSLoading.hpp"
#include "CompositeMonster.hpp"

GSInGame::GSInGame(std::list<Player *> &players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online, unsigned int nbCredits)
	: GameState("Game"), _idPlayer(0),
	  _players(players), _mode(mode), _map(map),
	  _nbPlayers(nbPlayers), _nbDie(0), _online(online),
	  _scores(4, 0), _scoreFonts(nbPlayers, this->getFont("buttonFont")),
	  _nameFonts(nbPlayers, this->getFont("buttonFont")), _rangeBegin(0), _rangeEnd(0),
	  _currentId(0), _fire(false), _elapsedTime(0), _nbCredits(nbCredits),
	  _gameOver(0) 
{
	Rules::setOnline(online);
}

GSInGame::~GSInGame()
{
	Core::CommandDispatcher::get().clear();
}

void		GSInGame::preload()
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
  this->addGroup("scoreBonus", 7);
  this->addGroup("map", 0);
  this->addGroup("traversableWalls", 5);
  this->addGroup("wallShot", 9);
  this->addGroup("shields", 40);
  this->addGroup("blackHoles", 3);
  this->addGroup("blackHoleEnd", 3);
  this->addGroup("particles", 3);
  this->addGroup("playerAuras", 3);
  this->addGroup("playerAurasPower", 4);
  this->addGroup("boss", 7);

  this->setCollisionGroups("players", "trigger", &Rules::playerTouchTrigger);
  this->setCollisionGroups("Wall", "shot", &Rules::limitWallTouchObject);
  this->setCollisionGroups("shields", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("shields", "wallShot", &Rules::wallTouchObject);
  this->setCollisionGroups("Wall", "monster", &Rules::limitWallTouchObject);
  this->setCollisionGroups("Wall", "monster2", &Rules::limitWallTouchObject);
  this->setCollisionGroups("shotWall", "playerShots", &Rules::limitWallTouchObject);
  this->setCollisionGroups("Wall", "playerShots", &Rules::limitWallTouchObject);
  this->setCollisionGroups("Wall", "wallShot", &Rules::limitWallTouchObject);
  this->setCollisionGroups("Wall", "particles", &Rules::limitWallTouchObject);
  this->setCollisionGroups("bottomInvisibleWall", "walls", &Rules::limitWallTouchObject);
  this->setCollisionGroups("bottomInvisibleWall", "breakableWalls", &Rules::limitWallTouchObject);
  this->setCollisionGroups("bottomInvisibleWall", "deadlyWalls", &Rules::limitWallTouchObject);
  this->setCollisionGroups("bottomInvisibleWall", "traversableWalls", &Rules::limitWallTouchObject);
  this->setCollisionGroups("grabs", "monster", &Rules::grabTouchMonster);
  this->setCollisionGroups("grabs", "monster2", &Rules::grabTouchMonster);
  this->setCollisionGroups("grabs", "players", &Rules::grabTouchPlayer);
  this->setCollisionGroups("playerShots", "monster", &Rules::shotTouchMonster);
  this->setCollisionGroups("playerShots", "monster2", &Rules::shotTouchMonster);
  this->setCollisionGroups("playerShots", "boss", &Rules::shotTouchMonster);
  this->setCollisionGroups("playerShots", "breakableWalls", &Rules::shotTouchMonster);
  this->setCollisionGroups("invisibleWalls", "players", &Rules::invisibleWallsTouchPlayers);
  this->setCollisionGroups("shot", "players", &Rules::shotTouchPlayer);
  this->setCollisionGroups("monster", "players", &Rules::monsterTouchPlayer);
  this->setCollisionGroups("boss", "players", &Rules::monsterTouchPlayer);
  this->setCollisionGroups("wallShot", "players", &Rules::shotTouchPlayer);
  this->setCollisionGroups("walls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("walls", "wallShot", &Rules::wallTouchObject);
  this->setCollisionGroups("walls", "playerShots", &Rules::wallTouchObject);
  this->setCollisionGroups("walls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("breakableWalls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("breakableWalls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("breakableWalls", "wallShot", &Rules::wallTouchObject);
  this->setCollisionGroups("deadlyWalls", "wallShot", &Rules::wallTouchObject);
  this->setCollisionGroups("deadlyWalls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("deadlyWalls", "playerShots", &Rules::wallTouchObject);
  this->setCollisionGroups("deadlyWalls", "players", &Rules::deadlyWallsTouchPlayers);
  this->setCollisionGroups("traversableWalls", "shot", &Rules::wallTouchObject);
  this->setCollisionGroups("traversableWalls", "playerShots", &Rules::wallTouchObject);
  this->setCollisionGroups("traversableWalls", "players", &Rules::wallsTouchPlayers);
  this->setCollisionGroups("grabs", "deadlyWalls", &Rules::grabTouchWall);
  this->setCollisionGroups("grabs", "breakableWalls", &Rules::grabTouchWall);
  this->setCollisionGroups("grabs", "walls", &Rules::grabTouchWall);
  this->setCollisionGroups("grabs", "traversableWalls", &Rules::grabTouchWall);
  this->setCollisionGroups("grabs", "invisibleWallsGrab", &Rules::grabTouchWall);
  this->setCollisionGroups("players", "scoreBonus", &Rules::playerTouchScore);
  this->setCollisionGroups("blackHoles", "shot", &Rules::blackHoleTouchObject);
  this->setCollisionGroups("blackHoles", "wallShot", &Rules::blackHoleTouchObject);
  this->setCollisionGroups("blackHoles", "monster", &Rules::blackHoleTouchObject);
  this->setCollisionGroups("blackHoles", "monster2", &Rules::blackHoleTouchObject);
  this->setCollisionGroups("blackHoles", "particles", &Rules::blackHoleTouchObject);
  this->setCollisionGroups("blackHoleEnd", "shot", &Rules::blackHoleEndTouchShot);
  this->setCollisionGroups("blackHoleEnd", "wallShot", &Rules::blackHoleEndTouchShot);
  this->setCollisionGroups("blackHoleEnd", "monster", &Rules::blackHoleEndTouchMonster);
  this->setCollisionGroups("blackHoleEnd", "monster2", &Rules::blackHoleEndTouchMonster);

  // load xml
  this->load(this->_map);

  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -1000, 4000, 980)), "shotWall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-1000, -2000, 8000, 1000)), "Wall");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, 1500, 8000, 1000)), "Wall");


  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-2000, VIEWY + 300,
	  8000, 1000)), "bottomInvisibleWall");

  int const large = 100;
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, -large + 30,
	  VIEWX, large)), "invisibleWallsGrab");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, -large + 30,
	  VIEWX, large)), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(-large + 30, 0,
	  large, VIEWY)), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(0, VIEWY - 30,
	  VIEWX, large)), "invisibleWalls");
  this->addGameObject(new Core::PhysicObject(*new Core::RectHitBox(VIEWX - 30, 0,
	  large, VIEWY)), "invisibleWalls");
}

void		GSInGame::registerShipCallbacks()
{
  Ship		*ship;

  for (std::list<Player *>::const_iterator it = this->_players.begin(); it != this->_players.end(); ++it)
  {
	  ship = (*it)->getShip();
	  if ((*it)->getType() == Player::KEYBOARD)
	  {
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			 *ship, &Ship::inputUp,
			  static_cast<int>(Core::Keyboard::Up));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputDown,
			  static_cast<int>(Core::Keyboard::Down));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputLeft,
			  static_cast<int>(Core::Keyboard::Left));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputRight,
			  static_cast<int>(Core::Keyboard::Right));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedUp,
			  static_cast<int>(Core::Keyboard::Up));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedDown,
			  static_cast<int>(Core::Keyboard::Down));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedLeft,
			  static_cast<int>(Core::Keyboard::Left));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedRight,
			  static_cast<int>(Core::Keyboard::Right));
		  this->getInput().registerInputCallback((*it)->getAction(Player::PAUSE).Type,
			  *this, &GSInGame::inputEscape,
			  static_cast<int>((*it)->getAction(Player::PAUSE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyReleased,
			  *ship, &Ship::inputReleasedSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputGrab1,
			  static_cast<int>((*it)->getAction(Player::GRAB1).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			  *ship, &Ship::inputGrab2,
			  static_cast<int>((*it)->getAction(Player::GRAB2).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
			 *ship, &Ship::inputGrab3,
			  static_cast<int>((*it)->getAction(Player::GRAB3).Key.Code));
		  this->getInput().registerInputCallback(Core::InputCommand::KeyPressed,
	   		 *ship, &Ship::specialPower,
			 static_cast<int>((*it)->getAction(Player::SPECIAL_POWER).Key.Code));
	  }
	  else
	  {
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickMoved,
			  *ship, &Ship::inputJoystickMoved, -1, (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::PAUSE).Type,
			  *this, &GSInGame::inputEscape,
			  static_cast<int>((*it)->getAction(Player::PAUSE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonPressed,
			  *ship, &Ship::inputFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
			  *ship, &Ship::inputReleasedFire,
			  static_cast<int>((*it)->getAction(Player::FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonPressed,
			  *ship, &Ship::inputSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback(Core::InputCommand::JoystickButtonReleased,
			  *ship, &Ship::inputReleasedSpecialFire,
			  static_cast<int>((*it)->getAction(Player::SPECIAL_FIRE).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB1).Type,
			 *ship, &Ship::inputGrab1,
			  static_cast<int>((*it)->getAction(Player::GRAB1).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB2).Type,
			 *ship, &Ship::inputGrab2,
			  static_cast<int>((*it)->getAction(Player::GRAB2).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::GRAB3).Type,
			 *ship, &Ship::inputGrab3,
			  static_cast<int>((*it)->getAction(Player::GRAB3).JoystickButton.Button),
			  (*it)->getType() - 1);
		  this->getInput().registerInputCallback((*it)->getAction(Player::SPECIAL_POWER).Type,
			 *ship, &Ship::specialPower,
		         static_cast<int>((*it)->getAction(Player::SPECIAL_POWER).JoystickButton.Button),
				 (*it)->getType() - 1);
	  }
  }
}

#include <iostream>
void		GSInGame::onStart()
{
	GameState *state = Core::GameStateManager::get().getGameState("Preload");
	if (state)
		state->pause();
	ScrollingSprite *obj1 = new ScrollingSprite(0, 0, VIEWX, VIEWY, ScrollingSprite::VERTICAL, 0.075);
	obj1->pushSprite("stars");
	this->addGameObject(obj1, "starobjects");
	ScrollingSprite *obj2 = new ScrollingSprite(0, 0, VIEWX, VIEWY, ScrollingSprite::VERTICAL, 0.2);
	obj2->pushSprite("clouds");
	this->addGameObject(obj2, "starobjects");
	ScrollingSprite *obj3 = new ScrollingSprite(0, 0, VIEWX, VIEWY, ScrollingSprite::VERTICAL, 0);
	obj3->pushSprite("ingame background");
	//	obj3->pushSprite("ingame background 2");
	//	obj3->pushSprite("ingame background 3");
	this->addGameObject(obj3, "background");
	 //test map
	_mapObj = static_cast<Map*>(this->getResource(this->_map, 5));
	this->addGameObject(_mapObj, "map");
	if (!_online)
		this->createShips();
  	this->registerShipCallbacks();
	MonsterGenerator	*generator = dynamic_cast<MonsterGenerator*>(this->_mapObj);
	if (generator)
		generator->setSeed(this->_rand());
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
	{"spawnspawner", &GSInGame::spawnspawner},
	{"spawncomposite", &GSInGame::spawncomposite},
	{"spawndecoration", &GSInGame::spawndecoration},
	{"spawnsound", &GSInGame::spawnsound},
	{"spawnend", &GSInGame::spawnend},
	{"respawnplayer", &GSInGame::respawnplayer},
	{"setseed", &GSInGame::setSeed},
	{"decreasePaused", &GSInGame::decreasePaused},
	{"increasePaused", &GSInGame::increasePaused},
	{"destroy", &GSInGame::destroy},
	{"ServerFire", &GSInGame::serverFire},
	{"ServerGrab", &GSInGame::serverGrab},
	{"ServerCannon", &GSInGame::serverCannon},
	{"killPlayer", &GSInGame::killPlayer},
	{"disableSpecialPower", &GSInGame::disableSpecialPower},
	{"bonus", &GSInGame::bonus},
	{"aura", &GSInGame::aura},
	{"reBind", &GSInGame::reBind},
	{"retry", &GSInGame::retry}
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

bool		GSInGame::classicMode()
{
	if (this->_nbDie == this->_players.size())
	{
	    if (this->_nbCredits > 0)
		{
			int	life = Modes::modesList[_mode].singleNbLife;
			
			this->_nbDie = 0;
			--this->_nbCredits;
			if (this->_players.size() != 1)
				life = Modes::modesList[_mode].multiNbLife;
			for (std::list<Player *>::iterator it = this->_players.begin();
				 it != this->_players.end(); ++it)
			{
				(*it)->getShip()->resetState();
				(*it)->setLife(life);
				(*it)->getShip()->setDead(false);
			}
			Core::GameStateManager::get().pushState(*new GSContinue(*this, this->_players, _nbCredits), (_online) ? NONE : PHYSIC);
		}
		else
		{
			this->gameover(false);
			return (true);
		}
	}
	return (false);
}

bool		GSInGame::highlanderMode()
{
  if (this->_nbDie == this->_players.size() - 1)
    {
      this->gameover(false);
      return (true);
    }
  return (false);
}

bool		GSInGame::playerDie()
{
	this->_nbDie++;
	if (!_mode != Modes::SURVIVAL_HIGHLANDER)
	  return (this->classicMode());
	else
	  return (this->highlanderMode());
}

void		GSInGame::setSeed(uint32_t seed)
{
	this->_rand.seed(seed);
}

void		GSInGame::gameover(bool victory)
{
  _gameOver = 0;
  this->pause(PHYSIC);
  Core::GameStateManager::get().pushState(*(new GSGameOver(victory, _players, _mode,
							   _map, _nbPlayers, _online)), Core::GameState::PHYSIC);
}

void		GSInGame::inputEscape(Core::InputCommand const &/*event*/)
{
  Core::GameState::Pause pause = (!_online ? (Core::GameState::PHYSIC) : (Core::GameState::NONE));
  Core::GameStateManager::get().pushState(*(new GSPauseMenu(*this, _players, _mode,
							    _map, _nbPlayers, _online)), pause);
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
	{
		obj->setVx(event.vx);
		obj->setVy(event.vy);
		obj->setPosition(event.x, event.y);
	}
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

void		GSInGame::spawnend(GameCommand const &)
{
	std::cout << "plop" << std::endl;
  this->gameover(true);
}

void		GSInGame::spawnspawner(GameCommand const &event)
{
	Core::BulletCommand		*spawner = new Core::BulletCommand(event.data, *this, event.x, event.y, event.vx, event.vy, event.boolean);
	spawner->setSeed(this->_rand());
	spawner->setScrollY(event.position);
	spawner->setRank(this->_nbPlayers);
	this->addGameObject(spawner, "spawners");
}

void		GSInGame::spawncomposite(GameCommand const &event)
{
	CompositeMonster *co = static_cast<CompositeMonster*>(this->getResource(event.data, 6));
	std::cout << "compospawn " << event.data << " " << co << std::endl;
	if (!co)
		return ;
	Core::BulletCommand *spawner = co->getBulletCommand(*this);
	spawner->setX(event.x);
	spawner->setY(event.y);
	spawner->setVx(event.vx);
	spawner->setVy(event.vy);
	spawner->setSeed(this->_rand());
	spawner->setScrollY(event.position);
	spawner->setRank(this->_nbPlayers);
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
	{
		sound->play();
		this->addSound(*sound);
	}
}

void		GSInGame::decreasePaused(GameCommand const &)
{
	this->getMap().decreasePaused();
}

void		GSInGame::increasePaused(GameCommand const &)
{
	this->getMap().increasePaused();
}

void		GSInGame::respawnplayer(GameCommand const &event)
{
	Ship*	ship = event.player->getShip();

	if (ship)
	  ship->setDead(false);
	if (event.player->getLife() == -1)
	  --this->_nbDie;
}

void		GSInGame::setSeed(GameCommand const &event)
{
	this->_rand.seed(event.idObject);
}

void		GSInGame::destroy(GameCommand const &event)
{
	DestroyCommand	const &cmd = reinterpret_cast<DestroyCommand const &>(event);

	std::list<size_t>::const_iterator it = cmd.ids.begin();
	Core::BulletCommand *obj = static_cast<Core::BulletCommand *>(this->getGameObject(*it));
	Core::BulletCommand *tmp = obj;
	it++;
	for (; it != cmd.ids.end() && tmp; ++it)
	{
		obj = tmp;
		tmp = static_cast<Core::BulletCommand *>(tmp->getChild(*it));
	}
	if (tmp && it == cmd.ids.end())
	{
	    if (tmp->score > 0)
	      {
			  for (int i = tmp->score / 10; i > 0; --i)
			  {
				  Core::BulletCommand *obj = new ScoreBonus(tmp->score, tmp->getX(), tmp->getY(), "bonus", *this);
			  //ConcreteObject *obj = new ScoreBonus("bonusScore", tmp->score, *(new Core::CircleHitBox(tmp->getX(), tmp->getY(), 40)), 0, 150, -40, -40);
				  this->addGameObject(obj, "scoreBonus");
			  }
	      }
		tmp->erase();
	}
}

void		GSInGame::serverFire(GameCommand const &cmd)
{
	Ship	*ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

	if (ship && ship->isGood(cmd.score))
	{
		switch (cmd.idResource)
		{
			case 0:
				ship->releaseFire();
				break;
			case 1:
				ship->fire();
				break;
			case 2:
				ship->specialFire();
				break;
			case 3:
				ship->releaseSpecialFire();
				break;
		};
	}
}

void		GSInGame::serverGrab(GameCommand const &cmd)
{
	Ship	*ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

	if (ship)
	{
		ship->launchGrab("grabs", cmd.idResource, cmd.x, cmd.y);
	}
}

void		GSInGame::serverCannon(GameCommand const &cmd)
{
	Ship	*ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

	if (ship)
	{
		if (cmd.data.empty())
			ship->releaseCannon(cmd.idResource);
		else
			ship->addCannon(new Cannon(cmd.data, *ship, *this, "bonus", "cannons", "playerShots", cmd.x, cmd.y), cmd.idResource);
	}
}

void		GSInGame::killPlayer(GameCommand const &cmd)
{
	Ship	*ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

	if (ship)
		ship->setDead(cmd.boolean, false);
}

void		GSInGame::disableSpecialPower(GameCommand const &cmd)
{
  	Ship*		ship = cmd.player->getShip();

  	if (ship)
  		ship->stopSpecialPower();
}

void        GSInGame::bonus(GameCommand const &cmd)
{
	Ship    *ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

	if (ship)
	{
		ship->specialPower();
		if (!cmd.boolean)
			return ;
		GameCommand	*cmd = new GameCommand("Bonus");
		cmd->idObject = ship->getId();
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
}

void		GSInGame::aura(GameCommand const &cmd)
{
	Ship    *ship = static_cast<Ship*>(this->getGameObject(cmd.idObject));

  	if (ship)
  		ship->displayAura();
}

void		GSInGame::reBind(GameCommand const &)
{
	while (Core::GameStateManager::get().getCurrentState().name != "bindPlayers")
		Core::GameStateManager::get().popState();
}

void		GSInGame::retry(GameCommand const &)
{
	while (Core::GameStateManager::get().getCurrentState().name != "Game")
		Core::GameStateManager::get().popState();
	for (std::list<Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	{
		if (_nbPlayers > 1)
			(*it)->setLife(-1);
		else
			(*it)->setLife(3);
	}
	GSLoading	*gs = new GSLoading(this->_players, this->_mode, this->_map, this->_players.size(), this->_online);
	Core::GameStateManager::get().changeState(*gs);
}

void		GSInGame::createShips()
{
  // player colors

  static struct {
    int r;
    int g;
    int b;
  } playerColors[] = {
		{96, 254, 1},
		{0, 255, 255},
		{255, 130, 0},
		{255, 220, 0}
  };

  Ship					*ship;
  unsigned int			i = 0;
  for (std::list<Player *>::const_iterator it = _players.begin(); it != _players.end(); ++it, ++i)
    {
		ship = new Ship(**it, *(*it)->getShipInfo(), *this, Color(playerColors[i].r, 
									  playerColors[i].g,
									  playerColors[i].b));
		ship->setY(600);
		ship->setX(i * 250 + 150);
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

Map&		GSInGame::getMap() const
{
  return *_mapObj;
}

unsigned int	GSInGame::getNbPlayers() const
{
  return (_nbPlayers);
}

unsigned int	GSInGame::getNbDie() const
{
  return (_nbDie);
}

void		GSInGame::setGameOver(int gameOver)
{
  this->_gameOver = gameOver;
}

void		GSInGame::update(double)
{
  if (_gameOver == 1)
    this->gameover(true);
  else if (_gameOver == 2)
    this->gameover(false);
}
