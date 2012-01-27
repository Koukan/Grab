#include <math.h>
#include "Bullet.hpp"
#include "CircleHitBox.hpp"

Bullet::Bullet(double x, double y, double vx, double vy)
	: PhysicObject(*new CircleHitBox(x, y, 1), vx, vy), _sprite(0)
{
}

Bullet::Bullet(HitBox &box, double vx, double vy)
	: PhysicObject(box, vx, vy), _sprite(0)
{
}

Bullet::Bullet(ResourceManager &resource, std::string const & sprite, HitBox &box,
	       double vx, double vy)
	: PhysicObject(box, vx, vy), _sprite(0)
{
  try
  {
	this->_sprite = resource.getSprite(sprite);
  }
  catch (...)
  {
	std::cerr << "Sprite \"" << sprite  << "\" not found" << std::endl;
  }
}

Bullet::~Bullet()
{
  delete this->_sprite;
}

void		Bullet::draw(double elapsedTime)
{
	if (this->_sprite)
	  this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y), elapsedTime);
}

void		Bullet::setSprite(ResourceManager &resource, std::string const &name)
{
	this->_sprite = resource.getSprite(name);
}

void		Bullet::setSprite(Sprite *sprite)
{
	this->_sprite = sprite;
}
