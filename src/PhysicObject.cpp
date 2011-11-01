#include "PhysicObject.hpp"

PhysicObject::PhysicObject(HitBox &hitbox, double vx, double vy) :
  DrawableObject(hitbox.getX(), hitbox.getY()), _vx(vx), _vy(vy), _hitBox(&hitbox)
{
}

PhysicObject::~PhysicObject(void)
{
	delete this->_hitBox;
}

double PhysicObject::getVx() const
{
  return (this->_vx);
}

double PhysicObject::getVy() const
{
  return (this->_vy);
}

HitBox	&PhysicObject::getHitBox() const
{
	return (*this->_hitBox);
}

void PhysicObject::setVx(double vx)
{
  this->_vx = vx;
}

void PhysicObject::setVy(double vy)
{
  this->_vy = vy;
}

void PhysicObject::setHitBox(HitBox &hitBox)
{
	this->_hitBox = &hitBox;
}

void	PhysicObject::move(double time)
{
  this->_x += this->_vx * time;
  this->_y += this->_vy * time;
}

bool PhysicObject::collide(PhysicObject &obj)
{
	this->_hitBox->setX(this->_x);
	this->_hitBox->setY(this->_y);
	obj.getHitBox().setX(obj.getX());
	obj.getHitBox().setY(obj.getY());
	return (this->_hitBox->collide(obj.getHitBox()));
}
