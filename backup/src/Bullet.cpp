#include <ClanLib/core.h>
#include "Bullet.hpp"
#include "CircleHitBox.hpp"

Bullet::Bullet(double x, double y, double direction, double speed)
	: PhysicObject(*new CircleHitBox(x, y, 5)), _direction(direction),
		_speed(speed), _sprite(0)
{
  _vx = speed * sin(direction);
  _vy = speed * cos(direction);
}

Bullet::Bullet(CL_ResourceManager &resource, std::string const & sprite,
	       double x, double y, double direction, double speed)
	: PhysicObject(*new RectHitBox(x, y, 5, 5)), _direction(direction),
		_speed(speed), _sprite(0)
{
  try
  {
  	_sprite = new Sprite(sprite, resource);
  }
  catch (CL_Exception e)
  {
	cl_log_event("system", "Sprite \"" + sprite + "\" not found");
  }
  _vx = speed * sin(direction);
  _vy = speed * cos(direction);
}

Bullet::~Bullet()
{
  delete _sprite;
}

void		Bullet::draw(double)
{
  if (_sprite)
    _sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y));
}

void		Bullet::setSprite(CL_ResourceManager &resource, std::string const &name)
{
  _sprite = new Sprite(name, resource);
}

void		Bullet::setSprite(Sprite *sprite)
{
  _sprite = sprite;
}
