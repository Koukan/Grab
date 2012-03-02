#include <cmath>
#include "Grab.hpp"
#include "RendererManager.hpp"
#include "Ship.hpp"

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Ship& ship, float speed, double offsetX, double offsetY) :
  ConcreteObject(spriteName, hitbox, vx, vy), _ship(ship), _returnToShip(false), _speed(speed), _offsetX(offsetX), _offsetY(offsetY)
{
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
      if (_x < 0 || _x > RendererManager::get().getWidth() || _y < 0 || _y > RendererManager::get().getHeight())
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
