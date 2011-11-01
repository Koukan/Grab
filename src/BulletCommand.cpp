#include "BulletCommand.hpp"
#include "Bullet.hpp"
#include "bulletmlparser.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BulletCommand::BulletCommand(BulletMLParser *parser, GameState &gstate,
		BulletName const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(parser), Bullet(x, y, direction, speed),
	  _turn(0), _end(false), _state(gstate),
	  _resource(gstate.getBulletResource(info))
{
  this->setSprite(_state, _resource.commandSprite);
}

BulletCommand::BulletCommand(BulletMLState *state, GameState &gstate,
		BulletName const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(state), Bullet(x, y, direction, speed),
	  _turn(0), _end(false), _state(gstate),
	  _resource(gstate.getBulletResource(info))
{
  this->setSprite(_state, _resource.commandSprite);
}

BulletCommand::BulletCommand(BulletMLState *state, GameState &gstate,
		BulletResource const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(state), Bullet(x, y, direction, speed),
	  _turn(0), _end(false),_state(gstate), _resource(info)
{
  this->setSprite(_state, _resource.commandSprite);
}

BulletCommand::~BulletCommand()
{
}

double		BulletCommand::getBulletDirection()
{
  return rtod(_direction);
}

double		BulletCommand::getAimDirection()
{
  return 0;
}

double		BulletCommand::getBulletSpeed()
{
  return this->_speed;
}

double		BulletCommand::getDefaultSpeed()
{
  return 1.0;
}

double		BulletCommand::getRank()
{
  return 0.5;
}

void		BulletCommand::createSimpleBullet(double direction, double speed)
{
  this->_state.addGameObject(new Bullet(_state, _resource.simpleSprite, _x, _y, dtor(direction), speed), _resource.simpleGroup);
}

void		BulletCommand::createBullet(BulletMLState* state,
				  	    double direction, double speed)
{
  BulletResource const	&resource = _state.getBulletResource(state->getLabel());

  this->_state.addGameObject(new BulletCommand(state, _state, resource, _x, _y, direction, speed), resource.commandGroup);
}

int		BulletCommand::getTurn()
{
  return static_cast<int>(_turn);
}

void		BulletCommand::doVanish()
{
  this->_end = true;
}

void		BulletCommand::doChangeDirection(double direction)
{
  this->_direction = dtor(direction);
  this->_vx = this->getBulletSpeedX();
  this->_vy = this->getBulletSpeedY();
}

void		BulletCommand::doChangeSpeed(double speed)
{
  this->_speed = speed;
  this->_vx = this->getBulletSpeedX();
  this->_vy = this->getBulletSpeedY();
}

void		BulletCommand::doAccelX(double speedx)
{
  this->_direction = atan2(this->_vy, speedx);
  this->_speed = sqrt(speedx * speedx + this->_vy * this->_vy);
}

void		BulletCommand::doAccelY(double speedy)
{
  this->_direction = atan2(speedy, this->_vx);
  this->_speed = sqrt(this->_vx * this->_vx + speedy * speedy);
}

double		BulletCommand::getBulletSpeedX()
{
  return this->_speed * sin(this->_direction);
}

double		BulletCommand::getBulletSpeedY()
{
  return this->_speed * cos(this->_direction);
}

void		BulletCommand::move(double time)
{
  _turn += time * 50;
  this->run();
  if (!this->_end)
    PhysicObject::move(time);
  else
    delete this;
}
