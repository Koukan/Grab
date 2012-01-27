#include "PhysicObject.hpp"
#include "Game.hpp"
#include "Callback.hpp"
#include "GameStateManager.hpp"

PhysicObject::PhysicObject(HitBox &hitbox, double vx, double vy) :
  DrawableObject(hitbox.getX(), hitbox.getY()), TreeElement(), _vx(vx), _vy(vy), _hitBox(&hitbox)
{
}

PhysicObject::~PhysicObject(void)
{
	if (this->_group)
		this->_group->getQuadTree().pop(*this);
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
	if (_vx && _vy)
		this->setPosition(this->_x + this->_vx * time, this->_y + this->_vy * time);
}

int PhysicObject::getWidthElement()
{
	return (this->_hitBox->getWidth());
}

int PhysicObject::getHeightElement()
{
	return (this->_hitBox->getHeight());
}

int PhysicObject::getXElement()
{
	return (static_cast<int>(this->_x));
}

int PhysicObject::getYElement()
{
	return (static_cast<int>(this->_y));
}

void PhysicObject::collide(TreeElement &elem)
{
	PhysicObject &obj = static_cast<PhysicObject &>(elem);

	this->_hitBox->setX(this->_x);
	this->_hitBox->setY(this->_y);
	obj.getHitBox().setX(obj.getX());
	obj.getHitBox().setY(obj.getY());
	if (this->_hitBox->collide(obj.getHitBox()))
	{
		collisionGroupsMap::const_iterator it = GameStateManager::get().getCurrentState().getCollisionGroups().find(stringPair(this->_group->getName(), obj.getGroup()->getName()));
		if (it != GameStateManager::get().getCurrentState().getCollisionGroups().end())
			(*it->second)(static_cast<GameObject &>(*this), static_cast<GameObject &>(obj));
	}
}
