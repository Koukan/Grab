#include "GameObject.hpp"
#include "GameObjectManager.hpp"
#include "GameState.hpp"

CORE_USE_NAMESPACE

GameObject::GameObject(double x, double y, double z, Group *group)
	: _x(x), _y(y), _z(z), _delete(0), _id(0), _group(group), _relativeObject(0)
{}

GameObject::~GameObject(void)
{
	if (this->_group)
		_group->removeObject(this);
	if (this->_relativeObject)
		this->_relativeObject->removeGameObject(*this);
	for (std::list<GameObject*>::iterator it = this->_objects.begin();
		 it != this->_objects.end(); it++)
		(*it)->setRelativeObject(0);
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

GameObject	*GameObject::getRelativeObject() const
{
	return this->_relativeObject;
}

int8_t		GameObject::isDelete() const
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

void		GameObject::setPosition(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}

void		GameObject::setGroup(Group *group)
{
  _group = group;
}

void		GameObject::setRelativeObject(GameObject *obj)
{
	if (this->_relativeObject)
		this->_relativeObject->removeGameObject(*this->_relativeObject);
	this->_relativeObject = obj;
	if (obj)
		obj->addGameObject(*this);
}

void		GameObject::erase()
{
	this->_delete = 1;
	this->_group->getState().addDeleteObject(this);
	for (std::list<GameObject*>::iterator it = this->_objects.begin();
		 it != this->_objects.end(); it++)
		(*it)->setRelativeObject(0);
}

void		GameObject::addGameObject(GameObject &obj)
{
	this->_objects.push_back(&obj);
}

void		GameObject::removeGameObject(GameObject &obj)
{
	for (std::list<GameObject*>::iterator it = this->_objects.begin();
		 it != this->_objects.end(); it++)
	{
		if (*it == &obj)
		{
			this->_objects.erase(it);
			return ;
		}
	}
}

void		GameObject::removeGroup()
{
	if (!this->_group)
		return ;
	this->_group->removeObject(this);
}
