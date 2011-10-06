#include "GameObjectManager.hpp"
#include "PhysicObject.hpp"
#include "DrawableObject.hpp"
#include "GameObject.hpp"

Group::Group()
	: physic(false), drawable(false)
{
}

Group::~Group()
{
  for (gameObjectSet::iterator it = this->objects.begin();
	it != this->objects.end(); it++)
  {
    (*it)->setGroup(0);
  }
}

void		Group::setFlags(int flags)
{
  this->physic = static_cast<bool>(flags & Group::PHYSIC);
  this->drawable = static_cast<bool>(flags & Group::DRAWABLE);
}

void		Group::setFlags(bool physic, bool drawable)
{
  this->physic = physic;
  this->drawable = drawable;
}

void		Group::addObject(GameObject *object)
{
  if (!this->drawable && !this->physic && this->objects.empty())
  {
    if (dynamic_cast<PhysicObject*>(object))
      this->physic = true;
    if (dynamic_cast<DrawableObject*>(object))
      this->drawable = true;
  }
  this->objects.insert(object);
  object->setGroup(this);
}

void		Group::removeObject(GameObject *object)
{
  this->objects.erase(object);
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

bool	GameObjectManager::existingGroup(const std::string &group) const
{
  return _groups.count(group);
}

bool	GameObjectManager::relatedGroups(const std::string &group1,
					 const std::string &group2,
					 bool reverse) const
{
  bool		test;

  test = _relatedGroups.count(stringPair(group1, group2));
  return (test) ? true :
	  reverse && _relatedGroups.count(stringPair(group2, group1));
}

void	GameObjectManager::addGroup(const std::string &group)
{
  _groups[group];
}

void	GameObjectManager::addGameObject(GameObject *object,
					 const std::string &group)
{
  _groups[group].addObject(object);
}

void	GameObjectManager::setRelatedGroups(const std::string &group1,
		const std::string &group2,
		void (*function)(GameObject&, GameObject&))
{
  _relatedGroups[stringPair(group1, group2)] =
	  new Callback(function);
}

void	GameObjectManager::setGroup(const std::string &name, int flags)
{
  _groups[name].setFlags(flags);
}
