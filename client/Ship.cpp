#include <math.h>
#include "Ship.hpp"
#include "Grab.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::ShipInfo const Ship::shipsList[] = {
  {"noname 1", "player1", "player3", 300, 400},
  {"noname 2", "player2", "player3", 300, 800},
  {"noname 3", "player3", "player3", 300, 200}
};

unsigned int const Ship::shipsListSize = sizeof(Ship::shipsList) / sizeof(*Ship::shipsList);

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName, float speed, int fireFrequency, int r, int g, int b, std::string const &group, unsigned int nbMaxGrabs)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false), _joyPosX(0), _joyPosY(0), _bulletFileName(bulletFileName),
	_playerBullet(new PlayerBullet(bulletFileName, Core::GameStateManager::get().getCurrentState(), "players", 0, 0))
{
	if (this->_playerBullet)
		Core::GameStateManager::get().getCurrentState().addGameObject(this->_playerBullet);
	for (int i = 0; i < Ship::NBACTIONS; ++i)
		this->_actions[i] = false;

	if (this->_sprite)
		this->_sprite->setColor(r, g, b);
	Core::GameStateManager::get().getCurrentState().addGameObject(this, group);
}

Ship::~Ship()
{
}

void Ship::launchGrab(std::string const &group)
{
  if (!_grabLaunched && _cannons.size() < _nbMaxGrabs)
   {
     Grab* grab = new Grab("bullet", *(new Core::CircleHitBox(this->getX(), this->getY(), 30)), 0, -200, *this, _speed * 2);
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

void Ship::addCannon(Cannon &cannon, std::string const &group)
{
  _cannons.push_back(&cannon);
  Core::GameStateManager::get().getCurrentState().addGameObject(&cannon, group);
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
		if (this->_playerBullet)
		{
			this->_playerBullet->setVx(0);
			this->_playerBullet->setVy(0);
		}
	}
	else
	{
		float distance = sqrt(static_cast<float>(vx * vx + vy * vy));
		this->_vx = vx * this->_speed / distance;
		this->_vy = vy * this->_speed / distance;
		if (this->_playerBullet)
		{
			this->_playerBullet->setVx(this->_vx);
			this->_playerBullet->setVy(this->_vy);
		}
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
		if (this->_playerBullet)
		{
			this->_playerBullet->setVx(this->_vx);
			this->_playerBullet->setVy(this->_vy);
		}
	}
	else
	{
		this->_vx = 0;
		this->_vy = 0;
		if (this->_playerBullet)
		{
			this->_playerBullet->setVx(0);
			this->_playerBullet->setVy(0);
		}
	}
}

void Ship::inputFire(Core::InputCommand const &cmd)
{
  this->launchGrab("grabs"); // tmp test
	if (this->_playerBullet)
		this->_playerBullet->isFiring(true);
}

void Ship::inputReleasedFire(Core::InputCommand const &cmd)
{
	if (this->_playerBullet)
		this->_playerBullet->isFiring(false);
}
