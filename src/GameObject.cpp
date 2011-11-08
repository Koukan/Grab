#include <iostream>
#include "GameObject.hpp"

GameObject::GameObject(double x, double y, Group *group)
	: _x(x), _y(y), _group(group)
{}

GameObject::~GameObject(void)
{
  if (this->_group)
    _group->removeObject(this);
}

double		GameObject::getX() const
{
  return _x;
}

double		GameObject::getY() const
{
  return _y;
}

Group		*GameObject::getGroup() const
{
  return _group;
}

void		GameObject::setX(double x)
{
  _x = x;
}

void		GameObject::setY(double y)
{
  _y = y;
}

void		GameObject::setPosition(double x, double y)
{
	_x = x;
	_y = y;
}

void		GameObject::setGroup(Group *group)
{
  _group = group;
}
