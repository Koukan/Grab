#include <cmath>
#include "Grab.hpp"


Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Ship& ship, float speed) :
  ConcreteObject(spriteName, hitbox, vx, vy), _ship(ship), _returnToShip(false), _speed(speed)
{
  //_static = true;
  //  _returnToShip = true;
	if (this->_sprite)
	{
		this->_xHitboxOffset = (this->_sprite->getWidth() - this->_hitBox->getWidth()) / 2;
		this->_yHitboxOffset = (this->_sprite->getHeight() - this->_hitBox->getHeight()) / 2;
	}
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

void	Grab::move(double time)
{
  if (!_returnToShip)
    {
      if (_x < 0 || _x > 1024 || _y < 0 || _y > 728)
	_returnToShip = true;
    }
  else
    {
      double vx, vy, angle;

      vx = _ship.getX() + _ship.getSprite().getWidth() / 2 - _x + this->getSprite().getWidth() / 2;
      vy = _ship.getY() + _ship.getSprite().getHeight() / 2 - _y + this->getSprite().getHeight() / 2;

      angle = atan2(vy, vx);

      this->_vx = cos(angle) * _speed;
      this->_vy = sin(angle) * _speed;
    }
  if (!this->_static && (this->_vx || this->_vy))
    {
      this->setPosition(this->_x + this->_vx * time, this->_y + this->_vy * time);
    }
}
