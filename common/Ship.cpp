#include <cmath>
#include "ShipInfo.hpp"
#include "Ship.hpp"
#include "Cannon.hpp"
#include "GameStateManager.hpp"
#include "CircleHitBox.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"
#include "Player.hpp"
#include "Converter.hpp"
#include "BlackHolePower.hpp"
#include "GameState.hpp"
#include "SpecialPower.hpp"
#include "Shield.hpp"
#include "Missile.hpp"
#ifdef _CLIENT_
#include "GSInGame.hpp"
#endif

Ship::Ship(Player &player, ShipInfo::ShipInfo const &info,
	   Core::GameState &state, Color const & color, int lifes,
	   unsigned int nbMaxGrabs)
	: ConcreteObject(info.spriteName, *new Core::CircleHitBox(0, 0, 5), 0, 0),
	  _caracs(info),
	  _player(player), _speed(info.speed), _tmpSpeed(info.speed),
	  _dead(false), _nbMaxGrabs(nbMaxGrabs), _grabLaunched(false),
	  _color(color),
	  _fireSound(state.getSound("playerShotSound")),
	  _joyPosX(0), _joyPosY(0),
	  _playerBullet(0), _concentratedPlayerBullet(0),
	  _score(0), _nbSecRespawn(0),
	  _timer(state.getFont("listGameFont")),
	  _targetx(0), _targety(0), _target(false),
	  _powerGauge(0), //will be reset to 0 when I finish my tests
	  _powerMax(info.powerMax),
	  _specialPower(0),
	  _specialPowerActive(false), _electricAura(0), _state(state),
	  _nbDeath(0), _lifes(lifes)
{
       state.addGameObject(this, "players");
       if (info.specialPowerType == ShipInfo::SHIELD)
	 _specialPower = new Shield(*this, _state);
       else if (info.specialPowerType == ShipInfo::MISSILE)
	 _specialPower = new Missile(*this, _state, _color);
       else if (info.specialPowerType == ShipInfo::BLACKHOLE)
	 _specialPower = new BlackHolePower(*this, _state);
	_cannons[0] = 0;
	_cannons[1] = 0;
	_cannons[2] = 0;
	_cannons[3] = 0;
	for (int i = 0; i < Ship::NBACTIONS; ++i)
		this->_actions[i] = false;

	if (this->_timer)
		this->_timer->setColor(/*r*/0, /*g*/0, /*b*/0);
	if (this->_sprite)
	{
		//this->_sprite->setColor(r, g, b);
		this->_xHitboxOffset = -this->_hitBox->getWidth() / 2;
		this->_yHitboxOffset = -this->_hitBox->getHeight() / 2;
		Core::Sprite *aura = state.getSprite("playerAura");
		if (aura)
		{
			ConcreteObject *obj = new ConcreteObject(aura, *new Core::CircleHitBox(0, 0, 1), 0, 0);
			obj->setLink(this);
			aura->setColor(_color.r, _color.g, _color.b);
			state.addGameObject(obj, "playerAuras");
		}
	}
	this->defineGrabPosition(info.grab1, 0, info.grabAngle1);
	this->defineGrabPosition(info.grab2, 1, info.grabAngle2);
	this->defineGrabPosition(info.grab3, 2, info.grabAngle3);
	player.setShip(this);
	_lastId = 0;
}

Ship::~Ship()
{
	if (this->_fireSound)
		delete this->_fireSound;
}

void	Ship::setPosition(double x, double y, double)
{
	_targetx = x + this->_vx * 0.03;
	_targety = y + this->_vy * 0.03;
	_target = true;
	double	angle = atan2(y - this->_targety, x - this->_targetx);
	this->_vx = cos(angle) * this->_speed;
	this->_vy = sin(angle) * this->_speed;
}

void	Ship::move(double time)
{
	if (_target == true)
	{
		double vx = this->_vx * time;
		double vy = this->_vy * time;
		if ((vx >= 0 && this->_x + vx > this->_targetx) ||
			(vx < 0 && this->_x + vx < this->_targetx))
		{
			this->_vx = 0;
			this->_x = this->_targetx;
		}
		if ((vy >= 0 && this->_y + vy > this->_targety) ||
			(vy < 0 && this->_y + vy < this->_targety))
		{
			this->_vy = 0;
			this->_y = this->_targety;
		}
		if (this->_vx == 0 && this->_vy == 0)
			this->_target = false;
	}
	this->Core::PhysicObject::move(time);
	this->updateBulletTrajectory();
	this->updateCannonsTrajectory();
	if ((this->_vx == 0 && this->_vy == 0) || this->_player.getType() == Player::ONLINE)
		return ;
	GameCommand	*move = new GameCommand("Move");
	move->idObject = this->getId();
	move->x = static_cast<int16_t>(this->getX());
	move->y = static_cast<int16_t>(this->getY());
	move->vx = this->getVx();
	move->vy = this->getVy();
	Core::CommandDispatcher::get().pushCommand(*move);
}

void 	Ship::launchGrab(std::string const &group, unsigned int nGrab, double x, double y)
{
	Grab* grab = new Grab("grab",
				*(new Core::CircleHitBox(x, y, 10)),
				*this, 180, _tmpSpeed * 2, nGrab, _grabsPositions[nGrab].first,
				_grabsPositions[nGrab].second, _angles[nGrab]);
	if (grab->getSprite())
		grab->getSprite()->setColor(this->_color.r, this->_color.g, this->_color.b);
	_state.addGameObject(grab, group);
	_grabLaunched = true;
}

void	Ship::setSpecialPowerActive(bool isActive)
{
	this->_specialPowerActive = isActive;
}

void Ship::setGrabLaunched(bool grabLaunched)
{
  _grabLaunched = grabLaunched;
}

bool Ship::getGrabLaunched() const
{
  return (_grabLaunched);
}

Player	&Ship::getPlayer() const
{
	return this->_player;
}

double Ship::getSpeed() const
{
  return (_speed);
}

void	Ship::addCannon(Cannon *cannon, unsigned int nGrab)
{
	if (cannon && nGrab < _nbMaxGrabs)
	{
		if (_cannons[nGrab])
			_cannons[nGrab]->erase();
		_cannons[nGrab] = cannon;
		cannon->setColor(_color.r, _color.g, _color.b);
		this->manageFire();
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
	//if (this->_dead)
	//	return ;
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

void Ship::manageFire()
{
	if (this->_actions[Ship::SPECIAL_FIRE] == true && !this->_dead)
	{
		if (!this->_concentratedPlayerBullet)
		{
			int constraint = 0;
			if (this->_caracs.xConstraint)
				constraint |= PhysicObject::X;
			if (this->_caracs.yConstraint)
				constraint |= PhysicObject::Y;
			this->_concentratedPlayerBullet = new PlayerBullet(this->_caracs.concentratedBulletFileName, this->getGroup()->getState(),
									"playerShots", this->_x + this->_caracs.xFireOffset,
									this->_y + this->_caracs.yFireOffset, this->_vx, this->_vy, 0, this, static_cast<PhysicObject::Constraint>(constraint));
			this->_concentratedPlayerBullet->setColor(_color.r, _color.g, _color.b);
			this->getGroup()->getState().addGameObject(this->_concentratedPlayerBullet, "spawner");
		}
		if (this->_playerBullet)
			this->_playerBullet->isFiring(false);
		if (this->_tmpSpeed == this->_speed)
		{
			this->_speed = this->_tmpSpeed * 0.3;
			this->_vx = this->_vx / this->_tmpSpeed * this->_speed;
			this->_vy = this->_vy / this->_tmpSpeed * this->_speed;
		}
		this->_concentratedPlayerBullet->isFiring(!this->_dead);
		//this->_playerBullet->isConcentrated(true);
		for (unsigned int i = 0; i < _nbMaxGrabs; ++i)
		{
			if (_cannons[i])
			{
				_cannons[i]->fire();
				if (_cannons[i]->getBullet())
					_cannons[i]->getBullet()->isConcentrated(!this->_dead);
			}
		}
		return ;
	}
	else if (this->_actions[Ship::FIRE] == true && !this->_dead)
	{
		if (this->_concentratedPlayerBullet)
			this->_concentratedPlayerBullet->isFiring(false);
		if (!this->_playerBullet)
		{
			this->_playerBullet = new PlayerBullet(this->_caracs.bulletFileName, this->getGroup()->getState(),
									"playerShots", this->_x + this->_caracs.xFireOffset,
									this->_y + this->_caracs.yFireOffset, this->_vx, this->_vy);
			this->_playerBullet->setColor(_color.r, _color.g, _color.b);
			this->getGroup()->getState().addGameObject(this->_playerBullet);
		}
		this->_playerBullet->isFiring(true);
		//this->_playerBullet->isConcentrated(false);
		for (unsigned int i = 0; i < _nbMaxGrabs; ++i)
		{
			if (_cannons[i])
			{
				_cannons[i]->fire();
				if (_cannons[i]->getBullet())
					_cannons[i]->getBullet()->isConcentrated(false);
			}
		}
	}
	else
	{
		if (this->_playerBullet)
			this->_playerBullet->isFiring(false);
		if (this->_concentratedPlayerBullet)
			this->_concentratedPlayerBullet->isFiring(false);
		for (unsigned int i = 0; i < _nbMaxGrabs; ++i)
		{
			if (_cannons[i])
				_cannons[i]->stopFire();
		}
	}
	this->_vx = this->_vx / this->_speed * this->_tmpSpeed;
	this->_vy = this->_vy / this->_speed * this->_tmpSpeed;
	this->_speed = this->_tmpSpeed;
}

void	Ship::fire()
{
	this->_actions[Ship::FIRE] = true;
	this->manageFire();
	if (!this->_actions[Ship::SPECIAL_FIRE] && this->_fireSound)
		this->_fireSound->play();
}

void	Ship::releaseFire()
{
	this->_actions[Ship::FIRE] = false;
	this->manageFire();
	if (!this->_actions[Ship::SPECIAL_FIRE] && this->_fireSound)
		this->_fireSound->pause();
}

void	Ship::specialFire()
{
	this->_actions[Ship::SPECIAL_FIRE] = true;
	this->manageFire();
	if (!this->_actions[Ship::FIRE] && this->_fireSound)
		this->_fireSound->play();
}

void	Ship::releaseSpecialFire()
{
	this->_actions[Ship::SPECIAL_FIRE] = false;
	this->manageFire();
	if (!this->_actions[Ship::FIRE] && this->_fireSound)
		this->_fireSound->pause();
}

bool	Ship::isGood(uint32_t id)
{
	if (id > this->_lastId)
	{
		this->_lastId = id;
		return true;
	}
	return false;
}

void Ship::inputFire(Core::InputCommand const& /*cmd*/)
{
	this->fire();
	Core::CommandDispatcher::get().pushCommand(*new GameCommand("Fire", this->_id, 1));
}

void Ship::inputReleasedFire(Core::InputCommand const& /*cmd*/)
{
	this->releaseFire();
	Core::CommandDispatcher::get().pushCommand(*new GameCommand("Fire", this->_id, 0));
}

void Ship::inputSpecialFire(Core::InputCommand const& /*cmd*/)
{
	this->specialFire();
	Core::CommandDispatcher::get().pushCommand(*new GameCommand("Fire", this->_id, 2));
}

void Ship::inputReleasedSpecialFire(Core::InputCommand const &)
{
	this->releaseSpecialFire();
	Core::CommandDispatcher::get().pushCommand(*new GameCommand("Fire", this->_id, 3));
}

void Ship::inputGrab1(Core::InputCommand const& /*cmd*/)
{
	if (this->_dead)
		return ;
  this->manageGrab("grabs", 0);
}

void Ship::inputGrab2(Core::InputCommand const& /*cmd*/)
{
	if (this->_dead)
		return ;
  this->manageGrab("grabs", 1);
}

void Ship::inputGrab3(Core::InputCommand const& /*cmd*/)
{
	if (this->_dead)
		return ;
  this->manageGrab("grabs", 2);
}

void Ship::grab4()
{
	if (this->_dead)
		return ;
  this->manageGrab("grabs", 3);
}

void Ship::kill() // tmp, I'm lazy and tired
{
  _dead = true;
  if (this->getSprite())
    this->getSprite()->setTransparency(0);
  this->resetPowerGauge();
  this->stopSpecialPower();
  this->manageFire();
}

void Ship::setDead(bool dead, bool command)
{
  	if (this->_dead == dead)
		return ;
	this->_dead = dead;
	if (!dead)
	{
		if (this->getSprite())
			this->getSprite()->setTransparency(1);
		this->manageFire();
		if (command)
		{
			GameCommand		*cmd = new GameCommand("deadPlayer");
			cmd->idObject = this->_id;
			cmd->boolean = false;
			Core::CommandDispatcher::get().pushCommand(*cmd);
		}
		return ;
	}
	this->resetPowerGauge();
	this->stopSpecialPower();
	this->manageFire();
	if (this->getSprite())
		this->getSprite()->setTransparency(0.4f);
	this->die();
	if (command)
	{
		GameCommand		*cmd = new GameCommand("deadPlayer");
		cmd->idObject = this->_id;
		cmd->boolean = true;
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
}

void			Ship::respawn()
{
  int nbSpawn =  2 + this->_nbDeath * 2;

    if (nbSpawn > 8)
      nbSpawn = 8;

  GameCommand	*cmd = new GameCommand("respawnplayer");
  cmd->player = &this->_player;
  this->getGroup()->getState().pushCommand(*cmd, nbSpawn * 1000); 
  this->setNbSecRespawn(nbSpawn);
  if (this->_timer)
    {
      this->_timer->setText(Net::Converter::toString<int>(this->_nbSecRespawn));
      this->_timer->setColor(255, 255, 255);
    }
}

void			Ship::die()
{
  if (this->_lifes != -1)
    {
      --this->_lifes;
      if (this->_lifes > 0)
	this->respawn();
      #ifdef _CLIENT_
      else
	static_cast<GSInGame&>(_state).playerDie();
      #endif
    }
  else // in this part, a "dead player" is a player in ghost mode
    {
      ++this->_nbDeath; // increase respawn timer
      #ifdef _CLIENT_
      GSInGame&	state = static_cast<GSInGame&>(_state);
			
      if (!state.playerDie())
	this->respawn();
      #endif
    }
}

bool Ship::isDead() const
{
	return this->_dead;
}

void Ship::draw(double elapsedTime)
{
	this->ConcreteObject::draw(elapsedTime);
	if (this->_dead && this->_nbSecRespawn > 0 && this->_timer)
	{
		if (this->_elapsedTime < 0)
		{
			--this->_nbSecRespawn;
			this->_timer->setText(Net::Converter::toString<int>(this->_nbSecRespawn));
			this->_elapsedTime += 1000;
		}
		else
			this->_elapsedTime -= elapsedTime;
	this->_timer->draw(static_cast<int>(this->_x - this->_timer->getWidth() / 2),
		static_cast<int>(this->_y - this->_timer->getHeight() / 2), elapsedTime);
	}
}

void Ship::manageGrab(std::string const &group, unsigned int nGrab)
{
	if (_cannons[nGrab])
	{
		this->releaseCannon(nGrab);
		GameCommand		*cmd = new GameCommand("updateCannon");
		cmd->idObject = this->_id;
		cmd->idResource = nGrab;
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
	else if (!_grabLaunched && nGrab < _nbMaxGrabs)
	{
		this->launchGrab(group, nGrab, this->getX(), this->getY());
		GameCommand	*cmd = new GameCommand("launchGrab");
		cmd->x = static_cast<int16_t>(this->getX());
		cmd->y = static_cast<int16_t>(this->getY());
		cmd->idResource = nGrab;
		cmd->idObject = this->_id;
		Core::CommandDispatcher::get().pushCommand(*cmd);
	}
}

void Ship::releaseCannon(unsigned int nb)
{
	if (nb > 4 || !_cannons[nb])
		return ;
	_cannons[nb]->stopFire();
	_cannons[nb]->erase();
	_cannons[nb] = 0;
}

void Ship::copyColor(Core::Sprite &sprite) const
{
	sprite.setColor(_color.r, _color.g, _color.b);
}

void Ship::updateCannonsTrajectory()
{
  PlayerBullet *bullet;

  for (unsigned int i = 0; i < _nbMaxGrabs; ++i)
    {
      if (_cannons[i])
	{
	  _cannons[i]->setX(this->_x + _cannons[i]->getOffsetX());
	  _cannons[i]->setY(this->_y + _cannons[i]->getOffsetY());
	  bullet = _cannons[i]->getBullet();
	  if (bullet)
	    {
	      bullet->setX(this->_x + _cannons[i]->getOffsetX());
	      bullet->setY(this->_y + _cannons[i]->getOffsetY());
	    }
	}
    }
}

void Ship::updateBulletTrajectory()
{
  if (this->_playerBullet)
    {
      this->_playerBullet->setX(this->_x + this->_caracs.xFireOffset);
      this->_playerBullet->setY(this->_y + this->_caracs.yFireOffset);
    }
  if (this->_concentratedPlayerBullet)
    {
      this->_concentratedPlayerBullet->setX(this->_x + this->_caracs.xFireOffset);
      this->_concentratedPlayerBullet->setY(this->_y + this->_caracs.yFireOffset);
    }
}

void Ship::defineGrabPosition(GrabPosition::Position position, unsigned int nGrab, int angle)
{
  if ((position & 8))
    _grabsPositions[nGrab].first = -_sprite->getWidth() / 2 - 20;
  else if ((position & 16))
    _grabsPositions[nGrab].first = 0;
  else if ((position & 32))
    _grabsPositions[nGrab].first = _sprite->getWidth() / 2 + 20;
  if ((position & 1))
    _grabsPositions[nGrab].second = -_sprite->getHeight() / 2 - 30;
  else if ((position & 2))
    _grabsPositions[nGrab].second = 0;
  else if ((position & 4))
    _grabsPositions[nGrab].second = _sprite->getHeight() / 2 + 20;
  _angles[nGrab] = angle;
}

unsigned int	Ship::getScore() const
{
  return (_score);
}

void		Ship::setScore(unsigned int score)
{
  _score = score;
}

Color const &	Ship::getColor() const
{
  return _color;
}

ShipInfo::ShipInfo const & Ship::getShipCaracs() const
{
  return _caracs;
}
void		Ship::setNbSecRespawn(int nbSec)
{
	this->_nbSecRespawn = nbSec;
}

unsigned int	Ship::getPowerGauge() const
{
  return (_powerGauge);
}

int		Ship::getLifes() const
{
  return (_lifes);
}

void		Ship::setLifes(int lifes)
{
  _lifes = lifes;
}

void		Ship::setNbDeath(int nbDeath)
{
  _nbDeath = nbDeath;
}

void		Ship::increasePowerGauge(unsigned int score)
{
  if (!_specialPowerActive)
    {
      _powerGauge += score;
      if (_powerGauge > _powerMax)
	_powerGauge = _powerMax;
      if (_powerGauge == _powerMax && !_electricAura)
	  {
		this->displayAura();
		if (this->_player.getType() == Player::ONLINE)
			return ;
		GameCommand		*cmd = new GameCommand("AuraActivated");
		cmd->idObject = this->_id;
		Core::CommandDispatcher::get().pushCommand(*cmd);
	  }
    }
}

void		Ship::specialPower(Core::InputCommand const&)
{
	GameCommand	*tmp = new GameCommand("bonus");
	tmp->idObject = this->getId();
	tmp->boolean = true;
	Core::CommandDispatcher::get().pushCommand(*tmp);
}

void		Ship::specialPower()
{
  if (_powerGauge == _powerMax && _specialPower)
    {
      this->resetPowerGauge();
      this->_specialPower->start();
    }
}

void		Ship::stopSpecialPower()
{
  if (_specialPower)
    _specialPower->stop();
}

void		Ship::resetState()
{
  for (int i = 0; i < Ship::NBACTIONS; ++i)
    {
      _actions[i] = false;
    }
}

void		Ship::resetPowerGauge()
{
  if (_electricAura)
    {
      _electricAura->erase();
      _electricAura = 0;
    }
  _powerGauge = 0;
}

void		Ship::displayAura()
{
	if (_electricAura)
		return ;
  Core::Sprite *powerAura = _state.getSprite("playerAuraPower");
  if (!powerAura)
	return ;
 	 _electricAura = new ConcreteObject(powerAura,
				  *new Core::CircleHitBox(0, 0, 5), 0, 0);
 	 _electricAura->setLink(this);
  	this->copyColor(*_electricAura->getSprite());
  	_state.addGameObject(_electricAura, "playerAurasPower");
}
