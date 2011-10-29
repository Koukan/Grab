#include "Bullet.hpp"

Bullet::Bullet(CL_ResourceManager &resource, std::string const & sprite, double x, double y,
	       double direction, double speed)
	: PhysicObject(x, y), _direction(direction), _speed(speed),
	  _sprite(sprite, resource)
{
  _vx = speed * sin(direction);
  _vy = speed * cos(direction);
}

Bullet::~Bullet()
{
}

void		Bullet::draw()
{
  _sprite.draw(this->_x, this->_y);
}
