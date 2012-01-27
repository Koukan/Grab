#include "ConcreteObject.hpp"

ConcreteObject::ConcreteObject(Sprite *sprite, HitBox &hitbox, double vx, double vy)
  : PhysicObject(hitbox, vx, vy), _sprite(sprite)
{
}

ConcreteObject::~ConcreteObject()
{
}

void			ConcreteObject::draw(double time)
{
	if (this->_sprite)
		this->_sprite->draw(this->_x, this->_y, time);
}
