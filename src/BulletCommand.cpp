#include "BulletCommand.hpp"
#include "Bullet.hpp"

inline double dtor(double x) { return x * M_PI / 180; }
inline double rtod(double x) { return x * 180 / M_PI; }

BulletCommand::BulletCommand(BulletMLParser *parser, GameState &gstate,
		std::string const &sprite,
		double x, double y, double direction, double speed)
	: BulletMLRunner(parser), Bullet(gstate, sprite, x, y, direction, speed),
	  _turn(0), _state(gstate)
{
}

BulletCommand::BulletCommand(BulletMLState *state, GameState &gstate,
		std::string const &sprite,
		double x, double y, double direction, double speed)
	: BulletMLRunner(state), Bullet(gstate, sprite, x, y, direction, speed),
	  _turn(0), _state(gstate)
{
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
  _state.addGameObject(new Bullet(_state, "shot", _x, _y, dtor(direction), speed), "shot", 5);
}

void		BulletCommand::createBullet(BulletMLState* state,
				  	    double direction, double speed)
{
  _state.addGameObject(new BulletCommand(state, _state, "bullet", _x, _y, direction, speed), "ship", 10);
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
  double	sy = getBulletSpeedY();
  _direction = atan2(sy, speedx);
  _speed = sqrt(speedx * speedx + sy * sy);
}

void		BulletCommand::doAccelY(double speedy)
{
  double	sx = getBulletSpeedX();
  _direction = atan2(speedy, sx);
  _speed = sqrt(sx * sx + speedy * speedy);
}

double		BulletCommand::getBulletSpeedX()
{
  return _speed * sin(_direction);
}

double		BulletCommand::getBulletSpeedY()
{
  return _speed * cos(_direction);
}

void		BulletCommand::move(int time)
{
  _turn += static_cast<double>(time) / 4;
  this->run();
  PhysicObject::move(time);
}
