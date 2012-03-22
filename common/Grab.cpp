#include <cmath>
#include "Grab.hpp"
#include "Ship.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, Ship& ship,
	   unsigned int angle, double speed, unsigned int nGrab,
	   double offsetX, double offsetY) :
  ConcreteObject(spriteName, hitbox, 0, 0, -10, -10), _ship(ship), _returnToShip(false),
	  _speed(speed), _offsetX(offsetX), _offsetY(offsetY), _nGrab(nGrab), _angle(angle)
{
  if (this->_sprite)
    {
      this->_xHitboxOffset = (this->_sprite->getWidth() - this->_hitBox->getWidth()) / 2;
      this->_yHitboxOffset = (this->_sprite->getHeight() - this->_hitBox->getHeight()) / 2;
    }

  this->_vx = sin(angle * M_PI / 180) * _speed;
  this->_vy = cos(angle * M_PI / 180) * _speed;
}

Grab::~Grab()
{}

void	Grab::setBulletScript(std::string const &bulletName)
{
  _bullet = bulletName;
}

std::string const &Grab::getBulletScript() const
{
  return _bullet;
}

bool	Grab::getReturnToShip() const
{
  return _returnToShip;
}

void	Grab::setReturnToShip(bool returnToShip)
{
  _returnToShip = returnToShip;
}

Ship	&Grab::getShip() const
{
  return (_ship);
}

unsigned int Grab::getNum() const
{
  return (_nGrab);
}

void	Grab::move(double time)
{
  if (_returnToShip)
    {
      double vx, vy, angle;

      vx = _ship.getX() + _ship.getSprite().getWidth() / 2 - _x - _sprite->getWidth() / 2;
      vy = _ship.getY() + _ship.getSprite().getHeight() / 2 - _y - _sprite->getHeight() / 2;

      angle = atan2(vy, vx);

      this->_vx = cos(angle) * _speed;
      this->_vy = sin(angle) * _speed;
    }
  PhysicObject::move(time);
}

double	Grab::getOffsetX() const
{
  return (this->_offsetX);
}

double	Grab::getOffsetY() const
{
  return (this->_offsetY);
}
