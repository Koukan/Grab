#include "GameObjectManager.hpp"
#include "PhysicObject.hpp"
#include "DrawableObject.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
#include <iostream>

Group::Group(GameState &state, int layer, std::string const &timeEffectGroup,
	     bool physic)
	: _gameState(state), _layer(layer), _physic(physic),
	  _timeEffectGroup(state.getTimeEffectGroup(timeEffectGroup))
{
}

Group::~Group()
{
  for (gameObjectSet::iterator it = this->_objects.begin();
	it != this->_objects.end(); it++)
    delete *it;
}


// getter
bool			Group::getPhysic() const
{
  return this->_physic;
}

int			Group::getLayer() const
{
  return this->_layer;
}

double			Group::getTimeEffect() const
{
  return this->_timeEffectGroup->getTimeEffect();
}

TimeEffectGroup		*Group::getTimeEffectGroup() const
{
  return this->_timeEffectGroup;
}

gameObjectSet const	&Group::getObjects(void) const
{
  return this->_objects;
}

void		Group::setLayer(int layer)
{
  this->_layer = layer;
}

void		Group::setPhysic(bool physicable)
{
  this->_physic = physicable;
}

void		Group::setTimeEffect(double timeEffect)
{
  this->_timeEffectGroup->setTimeEffect(timeEffect);
}

void		Group::setTimeEffectGroup(std::string const &timeEffectGroup)
{
  this->_timeEffectGroup = _gameState.getTimeEffectGroup(timeEffectGroup);
}

void		Group::setFlags(int layer, bool physic,
				std::string const &timeEffectGroup)
{
  this->_physic = physic;
  this->_layer = layer;
  this->setTimeEffectGroup(timeEffectGroup);
}

void		Group::addObject(GameObject *object)
{
  if (this->_objects.empty())
  {
    if (dynamic_cast<PhysicObject*>(object))
      this->_physic = true;
  }
  this->_objects.insert(object);
  object->setGroup(this);
}

void		Group::removeObject(GameObject *object)
{
  this->_objects.erase(object);
}

void		Group::draw(double) const
{
  if (this->_layer <= 0)
    return ;
  for (gameObjectSet::const_iterator it = this->_objects.begin();
	it != this->_objects.end(); it++)
  {
    static_cast<DrawableObject*>(*it)->draw();
  }
}

void		Group::deleteObjects()
{
  while (!this->_deletes.empty())
  {
    ::delete this->_deletes.top();
    this->_deletes.pop();
  }
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
  for (collisionGroupsMap::iterator it = this->_collisionGroups.begin();
	it != this->_collisionGroups.end(); it++)
    delete it->second;
}

bool	GameObjectManager::existingGroup(const std::string &group) const
{
  return this->_groups.count(group) > 0;
}

bool	GameObjectManager::collisionGroups(const std::string &group1,
					 const std::string &group2,
					 bool reverse) const
{
  return (this->_collisionGroups.count(stringPair(group1, group2)) > 0) ? true :
	  reverse && this->_collisionGroups.count(stringPair(group2, group1));
}

void	GameObjectManager::addGroup(const std::string &group, int layer,
				    std::string const &timeEffectGroup)
{
  if (this->_groups.count(group) == 0)
  {
    Group *groupe = new Group(static_cast<GameState&>(*this), layer, timeEffectGroup);
    this->_groups[group] = groupe;
    this->_display.insert(std::pair<int, Group*>(layer, groupe));
  }
}

void	GameObjectManager::addGameObject(GameObject *object,
					 const std::string &group, int layer)
{
  if (!object)
    return ;
  addGroup(group, layer);
  this->_groups[group]->addObject(object);
}

void	GameObjectManager::removeGameObject(GameObject *object)
{
  if (object->getGroup())
    object->getGroup()->removeObject(object);
}

void	GameObjectManager::setGroup(const std::string &name, int layer,
				    bool physic, std::string const &timeEffectGroup)
{
  addGroup(name, layer, timeEffectGroup);
  this->_groups[name]->setFlags(layer, physic, timeEffectGroup);
}

void	GameObjectManager::drawGameObject(double elapseTime) const
{
  for (groupsDisplay::const_iterator it = _display.begin(); it != _display.end(); it++)
    it->second->draw(elapseTime);
}

collisionGroupsMap const	&GameObjectManager::getCollisionGroups(void) const
{
  return this->_collisionGroups;
}

groupsMap const			&GameObjectManager::getGroups(void) const
{
  return this->_groups;
}
