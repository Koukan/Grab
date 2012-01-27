#ifndef		_GAMEOBJECTMANAGER_
#define 	_GAMEOBJECTMANAGER_

#include <map>
#include <set>
#include <string>
#include <stack>
#include "Callback.hpp"
#include "GameObject.hpp"
#include "TimeEffectManager.hpp"
#include "PhysicsSubscriber.hpp"
#include "PhysicsSubscriber2.hpp"
#include "PhysicsSubscriber3.hpp"
#include "QuadTree.hpp"
#include "PhysicObject.hpp"

class GameState;
class GameObjectManager;

class Group
{
  public:
	typedef std::set<GameObject*>	gameObjectSet;

    Group(GameState &state, std::string const &name, int layer,
	  uint32_t begin, uint32_t end, bool physic = false);
    ~Group();

    void	addObject(GameObject *object);
    void	removeObject(GameObject *object);
    void	addDelete(GameObject *object);
    void	deleteObjects();

    //setter
    void	setLayer(int layer);
    void	setPhysic(bool physicable);
    void	setTimeEffect(double timeEffect);
    void	setTimeEffectGroup(std::string const &timeEffectGroup);
    void	setFlags(int layer, bool physic, std::string const &timeEffectGroup);
	void	setRangeId(uint32_t begin, uint32_t end);

    //getter
    bool				getPhysic() const;
    int					getLayer() const;
    double				getTimeEffect() const;
    TimeEffectGroup		*getTimeEffectGroup() const;
    gameObjectSet const	&getObjects() const;
	QuadTree			&getQuadTree() const;
	std::string const	&getName() const;
	GameState			&getState() const;
	uint32_t			getId() const;

  private:
    GameState					&_gameState;
    int							_layer;
    bool						_physic;
    TimeEffectGroup				*_timeEffectGroup;
    gameObjectSet				_objects;
    std::stack<GameObject*>		_deletes;
	QuadTree					*_quadTree;
	std::string					_name;
	uint32_t					_beginId;
	uint32_t					_endId;
	mutable uint32_t			_currentId;
};

class GameObjectManager : public TimeEffectManager
{
  public:
	typedef std::pair<std::string, std::string>			stringPair;
	typedef	std::map<stringPair, IPhysicsSubscriber*>	collisionGroupsMap;
	typedef std::map<std::string, Group*>				groupsMap;
	typedef std::multimap<int, Group*>					groupsDisplay;

    GameObjectManager();
    virtual ~GameObjectManager();

    void	addGroup(const std::string &group, int layer = 1,
					 uint32_t beginId = 0, uint32_t endId = 0);
    bool	addGameObject(GameObject *object, const std::string &group = "default",
		    	int layer = 1);
    void	removeGameObject(GameObject *object);
	void	callCollision(PhysicObject &obj1, PhysicObject &obj2);

    // setter
    template <class InstanceClass>
    void	setCollisionGroups(const std::string &group1,
				const std::string &group2,
				void (InstanceClass::*function)(GameObject&));
    template <class InstanceClass>
    void	setCollisionGroups(const std::string &group1,
				const std::string &group2,
				void (InstanceClass::*function)(GameObject&, GameObject&));
    void	setCollisionGroups(const std::string &group1,
				const std::string &group2,
				void (*function)(GameObject&, GameObject&));
    void	setGroup(const std::string &name, int layer,
		    	bool physic, std::string const &timeEffectGroup);

    // getter
	GameObject					*getGameObject(uint32_t id);
    collisionGroupsMap const	&getCollisionGroups() const;
    groupsMap const				&getGroups() const;
    bool						existingGroup(const std::string &group) const;
    bool						collisionGroups(const std::string &group1,
    							const std::string &group2, bool reverse = true) const;
	void						addDeleteObject(GameObject *obj);
	void						deleteObjects();
	groupsDisplay const			&getDisplayObjects() const;
	uint32_t					getLastAttributedId() const;

  private:
	typedef	std::map<uint32_t, GameObject*>				IdMap;
	typedef	std::list<std::pair<uint32_t, uint32_t> >	Range;

	uint32_t					_id;
    collisionGroupsMap			_collisionGroups;
	IdMap						_objects;
	Range						_range;
    groupsMap					_groups;
    groupsDisplay				_display;
	std::set<GameObject*>		_deleteList;
};

#include "GameObjectManager.ipp"

#endif		/* _GAMEOBJECTMANAGER_ */
