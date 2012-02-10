#include "ConcreteObject.hpp"

ConcreteObject::ConcreteObject(Sprite *sprite, HitBox &hitbox, double vx, double vy)
  : PhysicObject(hitbox, vx, vy), _sprite(sprite)
{
}

ConcreteObject::~ConcreteObject()
{
	if (this->_sprite)
		delete this->_sprite;
}

void			ConcreteObject::draw(double time)
{
	if (this->_sprite)
		this->_sprite->draw(static_cast<int>(this->_x), static_cast<int>(this->_y), time);
}
