#include <math.h>
#include "Ship.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"

Ship::ShipInfo const Ship::shipsList[] = {
  {"Conqueror", "player1", "player3", 300, 400,
   Grab::MIDDLE_TOP, Grab::LEFT_BOTTOM_CORNER, Grab::RIGHT_BOTTOM_CORNER},
  {"Voyageer", "player2", "player3", 300, 800,
   Grab::MIDDLE_BOTTOM, Grab::LEFT_TOP_CORNER, Grab::RIGHT_TOP_CORNER},
  {"Obliterator", "player3", "player3", 300, 200,
   Grab::MIDDLE_TOP, Grab::LEFT_BOTTOM_CORNER, Grab::RIGHT_BOTTOM_CORNER}
};

unsigned int const Ship::shipsListSize = sizeof(Ship::shipsList) / sizeof(*Ship::shipsList);

Ship::Ship(std::string const &spriteName, std::string const &bulletFileName,
	   float speed, int fireFrequency, int r, int g, int b,
	   Grab::Position grab1, Grab::Position grab2, Grab::Position grab3,
	   std::string const &group, unsigned int nbMaxGrabs)
  : ConcreteObject(spriteName, *(new Core::CircleHitBox(0, 0, 5)), 0, 0),
    _speed(speed), _fireFrequency(fireFrequency),
    _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false),
     _joyPosX(0), _joyPosY(0),
    _bulletFileName(bulletFileName),
    _playerBullet(0)
{
	for (int i = 0; i < Ship::NBACTIONS; ++i)
		this->_actions[i] = false;

	if (this->_sprite)
	{
		this->_sprite->setColor(r, g, b);
		this->_xHitboxOffset = (this->_sprite->getWidth() - this->_hitBox->getWidth()) / 2;
		this->_yHitboxOffset = (this->_sprite->getHeight() - this->_hitBox->getHeight()) / 2;
	}
	Core::GameStateManager::get().getCurrentState().addGameObject(this, group);
	this->defineGrabPosition(grab1, 0);
	this->defineGrabPosition(grab2, 1);
	this->defineGrabPosition(grab3, 2);
}

Ship::~Ship()
{
}

void Ship::launchGrab(std::string const &group)
{
  if (!_grabLaunched && _cannons.size() < _nbMaxGrabs)
   {
     Grab* grab = new Grab("bullet", *(new Core::CircleHitBox(this->getX() + _sprite->getWidth() / 2, this->getY() + _sprite->getHeight() / 2, 30)), 0, -200, *this, _speed * 2, _grabsPositions[_cannons.size()].first, _grabsPositions[_cannons.size()].second);
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

float Ship::getSpeed() const
{
  return (_speed);
}

void Ship::addCannon(Cannon *cannon)
{
  if (cannon)
    {
      _cannons.push_back(cannon);
    }
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
	this->updateBulletTrajectory();
	this->updateCannonsTrajectory();
}

void Ship::inputUp(Core::InputCommand const &/*cmd*/)
{
	this->_actions[Ship::UP] = true;
	this->handleActions();
}

void Ship::inputDown(Core::InputCommand const &/*cmd*/)
{
	this->_actions[Ship::DOWN] = true;
	this->handleActions();
}

void Ship::inputLeft(Core::InputCommand const &/*cmd*/)
{
	this->_actions[Ship::LEFT] = true;
	this->handleActions();
}

void Ship::inputRight(Core::InputCommand const &/*cmd*/)
{
	this->_actions[Ship::RIGHT] = true;
	this->handleActions();
}

void Ship::inputReleasedUp(Core::InputCommand const& /*cmd*/)
{
	this->_actions[Ship::UP] = false;
	this->handleActions();
}

void Ship::inputReleasedDown(Core::InputCommand const& /*cmd*/)
{
	this->_actions[Ship::DOWN] = false;
	this->handleActions();
}

void Ship::inputReleasedLeft(Core::InputCommand const& /*cmd*/)
{
	this->_actions[Ship::LEFT] = false;
	this->handleActions();
}

void Ship::inputReleasedRight(Core::InputCommand const& /*cmd*/)
{
	this->_actions[Ship::RIGHT] = false;
	this->handleActions();
}

void Ship::inputJoystickMoved(Core::InputCommand const& cmd)
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
	this->updateBulletTrajectory();
	this->updateCannonsTrajectory();
}

void Ship::inputFire(Core::InputCommand const& /*cmd*/)
{
  this->launchGrab("grabs"); // tmp test
  /*  if (!this->_playerBullet)
  {
	  this->_playerBullet = new PlayerBullet(this->_bulletFileName, Core::GameStateManager::get().getCurrentState(),
		  "playerShots", this->_x + this->getSprite().getWidth() / 2, this->_y, this->_vx, this->_vy);
	  if (this->_playerBullet)
		Core::GameStateManager::get().getCurrentState().addGameObject(this->_playerBullet);
	  for (cannonContainer::iterator it = _cannons.begin(); it != _cannons.end(); ++it)
	    (*it)->fire();
	    }*/
}

void Ship::inputReleasedFire(Core::InputCommand const& /*cmd*/)
{
	if (this->_playerBullet)
	{
		this->_playerBullet->erase();
		this->_playerBullet = 0;
	}
	for (cannonContainer::iterator it = _cannons.begin(); it != _cannons.end(); ++it)
	  (*it)->stopFire();
}

void Ship::updateCannonsTrajectory()
{
  PlayerBullet *bullet;

  for (cannonContainer::iterator it = _cannons.begin(); it != _cannons.end(); ++it)
    {
      (*it)->setVx(this->_vx);
      (*it)->setVy(this->_vy);
      bullet = (*it)->getBullet();
      if (bullet)
	{
	  bullet->setVx(this->_vx);
	  bullet->setVy(this->_vy);
	}
    }
}

void Ship::updateBulletTrajectory()
{
  if (this->_playerBullet)
    {
      this->_playerBullet->setVx(this->_vx);
      this->_playerBullet->setVy(this->_vy);
    }
}

void Ship::defineGrabPosition(Grab::Position position, unsigned int nGrab)
{
  if ((position & 8))
    _grabsPositions[nGrab].first = -20;
  else if ((position & 16))
    _grabsPositions[nGrab].first = _sprite->getWidth() / 2;
  else if ((position & 32))
    _grabsPositions[nGrab].first = _sprite->getWidth() + 20;
  if ((position & 1))
    _grabsPositions[nGrab].second = -20;
  else if ((position & 2))
    _grabsPositions[nGrab].second = _sprite->getHeight() / 2;
  else if ((position & 4))
    _grabsPositions[nGrab].second = _sprite->getHeight() + 20;
}
