#include "GameObjectManager.hpp"
#include "PhysicObject.hpp"
#include "DrawableObject.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"

Group::Group(GameState &state, std::string const &name, int layer,
	     uint32_t begin, uint32_t end, bool physic)
	: _gameState(state), _layer(layer), _physic(physic),
	  _timeEffectGroup(state.getTimeEffectGroup("default")), _quadTree(new QuadTree()), _name(name), _beginId(begin), _endId(end), _currentId(begin)
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

QuadTree					&Group::getQuadTree() const
{
	return (*this->_quadTree);
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

void		Group::addObject(GameObject *object)
{
  if (this->_objects.empty())
  {
    if (dynamic_cast<PhysicObject*>(object))
      {
	this->_physic = true;
      }
  }
  if (this->_physic)
	  this->_quadTree->push(*static_cast<PhysicObject *>(object));
  if (!object->getId())
  	object->setId(this->getId());
  this->_objects.insert(object);
  object->setGroup(this);
}

void		Group::removeObject(GameObject *object)
{
	this->_objects.erase(object);
}

void		Group::deleteObjects()
{
	while (!this->_deletes.empty())
	{
		delete this->_deletes.top();
		this->_deletes.pop();
	}
}

GameObjectManager::GameObjectManager() : _id(0)
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
					 const std::string &group, int layer)
{
	if (!object)
		return false;
	addGroup(group, layer);
	this->_groups[group]->addObject(object);
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

GameObject	*GameObjectManager::getGameObject(uint32_t id)
{
	IdMap::iterator	it = this->_objects.find(id);

	if (it != this->_objects.end())
		return it->second;
	return 0;
}

GameObjectManager::collisionGroupsMap const
&GameObjectManager::getCollisionGroups(void) const
{
  return this->_collisionGroups;
}

GameObjectManager::groupsMap const
&GameObjectManager::getGroups(void) const
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
		this->_objects.erase((*tmp)->_id);
		delete *tmp;
		this->_deleteList.erase(tmp);
	}
}

GameObjectManager::groupsDisplay const	&GameObjectManager::getDisplayObjects() const
{
	return this->_display;
}

uint32_t			GameObjectManager::getLastAttributedId() const
{
 	return _id;
}
