#include "GameObjectManager.hpp"
#include "PhysicObject.hpp"
#include "DrawableObject.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"

CORE_USE_NAMESPACE

Group::Group(GameState &state, std::string const &name, int layer,
	     uint32_t begin, uint32_t end, bool physic)
	: _gameState(state), _layer(layer), _physic(physic),
	  _timeEffectGroup(state.getTimeEffectGroup("default")), _name(name), _beginId(begin), _endId(end), _currentId(begin)
{
}

Group::~Group()
{
	for (gameObjectSet::iterator it = this->_objects.begin();
	 	it != this->_objects.end(); it++)
	{
		(*it)->setGroup(0);
		delete *it;
	}
}

// getter
bool						Group::getPhysic() const
{
	return this->_physic;
}

int							Group::getLayer() const
{
	return this->_layer;
}

double						Group::getTimeEffect() const
{
	return this->_timeEffectGroup->getTimeEffect();
}

TimeEffectGroup				*Group::getTimeEffectGroup() const
{
	return this->_timeEffectGroup;
}

Group::gameObjectSet const	&Group::getObjects() const
{
	return this->_objects;
}

QuadTree					&Group::getQuadTree()
{
	return (this->_quadTree);
}

std::string const			&Group::getName() const
{
	return (this->_name);
}

GameState					&Group::getState() const
{
	return (this->_gameState);
}

uint32_t					Group::getId() const
{
	uint32_t			id = this->_currentId++;

	if (this->_currentId > this->_endId || this->_currentId == 0)
		this->_currentId = this->_beginId;
	return id;
}

void						Group::setLayer(int layer)
{
	this->_layer = layer;
}

void						Group::setPhysic(bool physicable)
{
	this->_physic = physicable;
}

void						Group::setTimeEffect(double timeEffect)
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

void		Group::addObject(GameObject *object, bool id)
{
  if (this->_objects.empty())
  {
	if (dynamic_cast<PhysicObject*>(object))
      {
	this->_physic = true;
      }
  }
  if (this->_physic)
	  this->_quadTree.push(*static_cast<PhysicObject *>(object));
  if (id && !object->getId())
  	object->setId(this->getId());
  this->_objects.insert(object);
  object->setGroup(this);
}

void		Group::removeObject(GameObject *object, bool id)
{
	this->_objects.erase(object);
	if (id)
		this->_gameState.removeObject(object->getId());
}


GameObjectManager::GameObjectManager() : _id(0)
{
}

GameObjectManager::~GameObjectManager()
{
	this->clear();
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
				    uint32_t beginId, uint32_t endId)
{
  if (this->_groups.count(group) == 0)
  {
	if (beginId == 0)
	{
		if (_range.empty())
		{
			beginId = 1;
			endId = 1000000;
		}
		else
		{
			beginId = _range.back().second + 1;
			endId = beginId + 1000000;
		}
	}
	_range.push_back(std::make_pair(beginId, endId));
    Group *groupe = new Group(static_cast<GameState&>(*this), group, layer, beginId, endId);
    this->_groups[group] = groupe;
    this->_display.insert(std::pair<int, Group*>(layer, groupe));
  }
}

bool	GameObjectManager::addGameObject(GameObject *object,
					 const std::string &group, bool id)
{
	if (!object)
		return false;
	addGroup(group);
	this->_groups[group]->addObject(object, id);
	if (id)
		this->_objects[object->_id] = object;
	return true;
}

void	GameObjectManager::removeGameObject(GameObject *object)
{
	if (object->getGroup())
		object->getGroup()->removeObject(object);
	IdMap::iterator	it = this->_objects.find(object->_id);
	if (it != this->_objects.end() && it->second == object)
		this->_objects.erase(it);
}

void	GameObjectManager::callCollision(PhysicObject &obj1,
										 PhysicObject &obj2)
{
		collisionGroupsMap::iterator it =
			this->_collisionGroups.find(stringPair(obj1.getGroup()->getName(),
								   			obj2.getGroup()->getName()));

		if (it != this->_collisionGroups.end())
			(*it->second)(obj1, obj2);
}

void	GameObjectManager::setGroup(const std::string &name, int layer,
				    bool physic, std::string const &timeEffectGroup)
{
	addGroup(name, layer);
	this->_groups[name]->setFlags(layer, physic, timeEffectGroup);
}

void	GameObjectManager::setCollisionGroups(
			const std::string &group1, const std::string &group2,
			void (*function)(GameObject&, GameObject&))
{
	_collisionGroups[stringPair(group1, group2)] =
		new PhysicsSubscriber3(function);
}

void	GameObjectManager::setBeginId(uint32_t begin)
{
	this->_id = begin;
}

GameObject	*GameObjectManager::getGameObject(uint32_t id)
{
	IdMap::iterator	it = this->_objects.find(id);

	if (it != this->_objects.end())
		return it->second;
	return 0;
}

GameObjectManager::collisionGroupsMap const &GameObjectManager::getCollisionGroups() const
{
  return this->_collisionGroups;
}

GameObjectManager::groupsMap const	&GameObjectManager::getGroups() const
{
  return this->_groups;
}

Group			*GameObjectManager::getGroup(std::string const &name) const
{
	groupsMap::const_iterator it = this->_groups.find(name);

	if (it != this->_groups.end())
		return it->second;
	return 0;
}

void			GameObjectManager::addDeleteObject(GameObject *obj)
{
	if (obj)
		this->_deleteList.insert(obj);
}

void			GameObjectManager::deleteObjects()
{
	for (std::set<GameObject *>::iterator it = this->_deleteList.begin(); it != this->_deleteList.end(); it++)
	{
		if ((*it)->isDelete() == 1)
		{
			this->_objects.erase((*it)->_id);
			delete *it;
		}
		else
			(*it)->removeGroup();
	}
	this->_deleteList.clear();
}

GameObjectManager::groupsDisplay const	&GameObjectManager::getDisplayObjects() const
{
	return this->_display;
}

uint32_t			GameObjectManager::getLastAttributedId() const
{
 	return _id;
}

void				GameObjectManager::removeObject(uint32_t id)
{
	this->_objects.erase(id);
}

void				GameObjectManager::clear()
{
	IdMap::iterator	tmp;
	for (IdMap::iterator it = this->_objects.begin();
		 it != this->_objects.end();)
	{
		tmp = it++;
		delete tmp->second;
	}
	for (collisionGroupsMap::iterator it = this->_collisionGroups.begin();
		 it != this->_collisionGroups.end(); it++)
		delete it->second;
	for (groupsMap::iterator it = this->_groups.begin();
		 it != this->_groups.end(); it++)
		delete it->second;

	this->_objects.clear();
	this->_collisionGroups.clear();
	this->_groups.clear();
	this->_deleteList.clear();
}