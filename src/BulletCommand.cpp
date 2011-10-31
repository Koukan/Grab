#include "BulletCommand.hpp"
#include "Bullet.hpp"
#include "bulletmlparser.h"

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BulletCommand::BulletCommand(BulletMLParser *parser, GameState &gstate,
		BulletName const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(parser), Bullet(x, y, direction, speed),
	  _turn(0), _state(gstate), _resource(gstate.getBulletResource(info))
{
  this->setSprite(_state, _resource.commandSprite);
}

BulletCommand::BulletCommand(BulletMLState *state, GameState &gstate,
		BulletName const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(state), Bullet(x, y, direction, speed),
	  _turn(0), _state(gstate), _resource(gstate.getBulletResource(info))
{
  this->setSprite(_state, _resource.commandSprite);
}

BulletCommand::BulletCommand(BulletMLState *state, GameState &gstate,
		BulletResource const &info,
		double x, double y, double direction, double speed)
	: BulletMLRunner(state), Bullet(x, y, direction, speed),
	  _turn(0), _state(gstate), _resource(info)
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
  return _speed;
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
  _state.addGameObject(new Bullet(_state, _resource.simpleSprite, _x, _y, dtor(direction), speed), _resource.simpleGroup);
}

void		BulletCommand::createBullet(BulletMLState* state,
				  	    double direction, double speed)
{
  BulletResource const	&resource = _state.getBulletResource(state->getLabel());

  _state.addGameObject(new BulletCommand(state, _state, resource, _x, _y, direction, speed), resource.commandGroup);
}

int		BulletCommand::getTurn()
{
  return static_cast<int>(_turn);
}

void		BulletCommand::doVanish()
{
  _state.removeGameObject(this);
  this->getGroup()->addDelete(this);
}

void		BulletCommand::doChangeDirection(double direction)
{
  _direction = dtor(direction);
  _vx = getBulletSpeedX();
  _vy = getBulletSpeedY();
}

void		BulletCommand::doChangeSpeed(double speed)
{
  _speed = speed;
  _vx = getBulletSpeedX();
  _vy = getBulletSpeedY();
}

void		BulletCommand::doAccelX(double speedx)
{
  _direction = atan2(_vy, speedx);
  _speed = sqrt(speedx * speedx + _vy * _vy);
}

void		BulletCommand::doAccelY(double speedy)
{
  _direction = atan2(speedy, _vx);
  _speed = sqrt(_vx * _vx + speedy * speedy);
}

double		BulletCommand::getBulletSpeedX()
{
  return _speed * sin(_direction);
}

double		BulletCommand::getBulletSpeedY()
{
  return _speed * cos(_direction);
}

void		BulletCommand::move(double time)
{
  _turn += time * 50;
  this->run();
  PhysicObject::move(time);
}
