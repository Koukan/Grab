#include "Grab.hpp"

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Ship& ship, float speed) :
  ConcreteObject(spriteName, hitbox, vx, vy), _ship(ship), _returnToShip(false), _speed(speed)
{
  //_static = true;
  //  _returnToShip = true;
}

Grab::~Grab()
{}

void	Grab::setBulletScript(std::string const &bulletName)
{
  _bullet = bulletName;
}

bool	Grab::getReturnToShip() const
{
  return _returnToShip;
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
      double vx, vy;

      vx = _ship.getX() + _ship.getSprite().getWidth() / 2 - _x + this->getSprite().getWidth() / 2;
      vy = _ship.getY() + _ship.getSprite().getHeight() / 2 - _y + this->getSprite().getHeight() / 2;

      double angle = atan2(vy, vx);

      this->_vx = cos(angle) * _speed;
      this->_vy = sin(angle) * _speed;
    }
  if (!this->_static && (this->_vx || this->_vy))
    {
      this->setPosition(this->_x + this->_vx * time, this->_y + this->_vy * time);
    }
}
