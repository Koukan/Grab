#include "Grab.hpp"

Grab::Grab(std::string const &spriteName, Core::HitBox& hitbox, double vx, double vy, Ship& ship, float speed) :
  ConcreteObject(spriteName, hitbox, vx, vy), _ship(ship), _returnToShip(false), _speed(speed)
{}

Grab::~Grab()
{}

void	Grab::setBulletScript(std::string const &bulletName)
{
  _bullet = bulletName;
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
  int vx, vy;

  if (_returnToShip)
    {
      vx = ((_ship.getX() /*+ _ship.getSprite().getWidth() / 2*/ > _x) ? 1 : -1); // height doesn't take into account the scale, so it's always wrong...
      vy = ((_ship.getY() /*+ _ship.getSprite().getHeight() / 2*/ > _y) ? 1 : -1);
    }
  else
    {
      vx = _vx;
      vy = _vy;
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
  if (!this->_static && (this->_vx || this->_vy))
    {
      this->setPosition(this->_x + this->_vx * time, this->_y + this->_vy * time);
    }

}
