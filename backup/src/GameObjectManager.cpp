#include "GameObjectManager.hpp"
#include "PhysicObject.hpp"
#include "DrawableObject.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
#include <iostream>

Group::Group(GameState &state, int layer, std::string const &timeEffectGroup, std::string const &name,
	     bool physic)
	: _gameState(state), _layer(layer), _physic(physic),
	  _timeEffectGroup(state.getTimeEffectGroup(timeEffectGroup)), _quadTree(new QuadTree()), _name(name)
{
}

Group::~Group()
{
  for (gameObjectSet::iterator it = this->_objects.begin();
	it != this->_objects.end(); it++)
    delete *it;
  delete this->_quadTree;
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

Group::gameObjectSet const	&Group::getObjects(void) const
{
	return this->_objects;
}

QuadTree	&Group::getQuadTree() const
{
	return (*this->_quadTree);
}

std::string const &Group::getName() const
{
	return (this->_name);
}

GameState	&Group::getState()
{
	return (this->_gameState);
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
  if (this->_physic)
	  this->_quadTree->push(*static_cast<PhysicObject *>(object));
  this->_objects.insert(object);
  object->setGroup(this);
}

void		Group::removeObject(GameObject *object)
{
	this->_objects.erase(object);
}

/*void		Group::draw(double elapseTime) const
{
	if (this->_layer <= 0)
		return ;
	gameObjectSet::const_iterator		it2;

	for (gameObjectSet::const_iterator it = this->_objects.begin();
			it != this->_objects.end();)
	{
		it2 = it++;
		static_cast<DrawableObject*>(*it2)->draw(elapseTime);
	}
}*/

void		Group::deleteObjects()
{
	while (!this->_deletes.empty())
	{
		delete this->_deletes.top();
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
    Group *groupe = new Group(static_cast<GameState&>(*this), layer, timeEffectGroup, group);
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

/*void	GameObjectManager::drawGameObject() const
{
  for (groupsDisplay::const_iterator it = _display.begin(); it != _display.end(); it++)
    it->second->draw(it->second->getTimeEffectGroup()->getElapseTime());
}*/

collisionGroupsMap const	&GameObjectManager::getCollisionGroups(void) const
{
  return this->_collisionGroups;
}

groupsMap const			&GameObjectManager::getGroups(void) const
{
  return this->_groups;
}
void			GameObjectManager::addDeleteObject(GameObject *obj)
{
	this->_deleteList.insert(obj);
}

void			GameObjectManager::deleteObjects()
{
	std::set<GameObject *>::iterator	tmp;

	for (std::set<GameObject *>::iterator it = this->_deleteList.begin(); it != this->_deleteList.end();)
	{
		tmp = it++;
		delete *tmp;
		this->_deleteList.erase(tmp);
	}
}

GameObjectManager::groupsDisplay const	&GameObjectManager::getDisplayObjects() const
{
	return this->_display;
}
