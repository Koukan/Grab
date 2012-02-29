#include <math.h>
#include "Ship.hpp"
#include "Grab.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"
#include "BulletCommand.hpp"

Ship::ShipInfo const Ship::shipsList[] = {
  {"noname 1", "player1", "bossMetroid", 300, 400},
  {"noname 2", "player2", "bossMetroid", 300, 800},
  {"noname 3", "player3", "bossMetroid", 300, 200}
};

unsigned int const Ship::shipsListSize = sizeof(Ship::shipsList) / sizeof(*Ship::shipsList);

<<<<<<< HEAD
Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, unsigned int nbMaxGrabs)
=======
Ship::Ship(std::string const &spriteName, std::string const &/*bulletFileName*/, float speed, int fireFrequency, int r, int g, int b, std::string const &group, unsigned int nbMaxGrabs)
>>>>>>> 6d625c20b9c58dc2eb3fe61bcb22f3e6e7f0041a
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false), _joyPosX(0), _joyPosY(0), _bulletFileName(bulletFileName)
{
	for (int i = 0; i < Ship::NBACTIONS; ++i)
		this->_actions[i] = false;

	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
<<<<<<< HEAD
}

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::pair<int, int> grabs[4], unsigned int nbMaxGrabs)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false), _joyPosX(0), _joyPosY(0), _bulletFileName(bulletFileName)
{
	for (int i = 0; i < Ship::NBACTIONS; ++i)
		this->_actions[i] = false;

	if (this->_sprite)
		this->_sprite->setColor(r, g, b);

	Grab *grab;
	for (unsigned int i = 0; i < nbMaxGrabs; ++i)
	  {
	    grab = new Grab("weapon", *(new Core::CircleHitBox(grabs[i].first, grabs[i].second, 5)), 0, 0, *this);
	_grabs.push_back(grab);
	  }
=======
      Core::GameStateManager::get().getCurrentState().addGameObject(this, group);
>>>>>>> 6d625c20b9c58dc2eb3fe61bcb22f3e6e7f0041a
}

Ship::~Ship()
{
}

void Ship::launchGrab(std::string const &group)
{
  if (/*!_grabLaunched &&*/ _cannons.size() < _nbMaxGrabs)
    {
      Grab* grab = new Grab("bullet", *(new Core::RectHitBox(this->getX(), this->getY(), 100, 100)), 0, -100, *this, _speed * 2);
      Core::GameStateManager::get().getCurrentState().addGameObject(grab, group);
      _grabLaunched = true;
    }
}

void Ship::setGrabLaunched(bool grabLaunched)
{
  _grabLaunched = grabLaunched;
}

bool Ship::getGrabLaunched() const
{
  return (_grabLaunched);
}

void Ship::addCannon(Cannon *cannon)
{
  if (cannon)
    _cannons.push_back(cannon);
}

void Ship::handleActions()
{
	int vx;
	int vy;

	if (this->_actions[Ship::UP])
	{
		if (this->_actions[Ship::DOWN])
			vy = 0;
		else
			vy = -1;
	}
	else
	{
		if (this->_actions[Ship::DOWN])
			vy = 1;
		else
			vy = 0;
	}

	if (this->_actions[Ship::LEFT])
	{
		if (this->_actions[Ship::RIGHT])
			vx = 0;
		else
			vx = -1;
	}
	else
	{
		if (this->_actions[Ship::RIGHT])
			vx = 1;
		else
			vx = 0;
	}

	if (vx == 0 && vy == 0)
	{
		this->_vx = 0;
		this->_vy = 0;
	}
	else
	{
		float distance = sqrt(static_cast<float>(vx * vx + vy * vy));
		this->_vx = vx * this->_speed / distance;
		this->_vy = vy * this->_speed / distance;
	}
}

void Ship::inputUp(Core::InputCommand const &cmd)
{
	this->_actions[Ship::UP] = true;
	this->handleActions();
}

void Ship::inputDown(Core::InputCommand const &cmd)
{
	this->_actions[Ship::DOWN] = true;
	this->handleActions();
}

void Ship::inputLeft(Core::InputCommand const &cmd)
{
	this->_actions[Ship::LEFT] = true;
	this->handleActions();
}

void Ship::inputRight(Core::InputCommand const &cmd)
{
	this->_actions[Ship::RIGHT] = true;
	this->handleActions();
}

void Ship::inputReleasedUp(Core::InputCommand const &cmd)
{
	this->_actions[Ship::UP] = false;
	this->handleActions();
}

void Ship::inputReleasedDown(Core::InputCommand const &cmd)
{
	this->_actions[Ship::DOWN] = false;
	this->handleActions();
}

void Ship::inputReleasedLeft(Core::InputCommand const &cmd)
{
	this->_actions[Ship::LEFT] = false;
	this->handleActions();
}

void Ship::inputReleasedRight(Core::InputCommand const &cmd)
{
	this->_actions[Ship::RIGHT] = false;
	this->handleActions();
}

void Ship::inputJoystickMoved(Core::InputCommand const &cmd)
{
	static float const limit = 50;

	if (cmd.JoystickMove.Axis == Core::Joystick::X)
		this->_joyPosX = cmd.JoystickMove.Position;
	else if (cmd.JoystickMove.Axis == Core::Joystick::Y)
		this->_joyPosY = cmd.JoystickMove.Position;

	float distance = this->_joyPosX * this->_joyPosX + this->_joyPosY * this->_joyPosY;
	if (distance >= limit * limit)
	{
		distance = ::sqrt(distance);
		this->_vx = this->_joyPosX * this->_speed / distance;
		this->_vy = this->_joyPosY * this->_speed / distance;
	}
	else
	{
		this->_vx = 0;
		this->_vy = 0;
	}
}

void Ship::inputFire(Core::InputCommand const &cmd)
{
	this->fire();
}

void Ship::fire()
{
	Core::GameState &state = Core::GameStateManager::get().getCurrentState();
	Core::BulletCommand *bullet = new Core::BulletCommand(this->_bulletFileName, state, this->_x, this->_y);
	state.addGameObject(bullet);
}
