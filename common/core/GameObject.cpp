#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "GameState.hpp"

GameObject::GameObject(double x, double y, Group *group)
	: _x(x), _y(y), _delete(false), _id(0), _group(group)
{}

GameObject::~GameObject(void)
{
  if (this->_group)
    _group->removeObject(this);
}

uint32_t	GameObject::getId() const
{
	return this->_id;
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

bool		GameObject::isDelete() const
{
	return (this->_delete);
}

void		GameObject::setId(uint32_t id)
{
	this->_id = id;
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

void		GameObject::erase()
{
	this->_delete = true;
	this->_group->getState().addDeleteObject(this);
}
