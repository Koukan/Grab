#ifndef		_GAMEOBJECTMANAGER_
#define 	_GAMEOBJECTMANAGER_

#include <map>
#include <set>
#include <string>
#include <stack>
#include "Callback.hpp"
#include "TimeEffectManager.hpp"

class GameObject;
class GameObjectManager;

typedef std::set<GameObject*>	gameObjectSet;

class Group
{
  public:
    Group(int layer, std::string const &timeEffectGroup, bool physic = false);
    ~Group();
    bool			getPhysic() const;
    int				getLayer() const;
    double			getTimeEffect() const;
    gameObjectSet const		&getObjects() const;
    void			setLayer(int layer);
    void			setTimeEffect(std::string const &name);
    void			setFlags(int layer, bool physic, std::string const &timeEffectGroup);
    void			addObject(GameObject *object);
    void			removeObject(GameObject *object);
    void			draw(double elapseTime) const;
    void			addDelete(GameObject *object);
    void			deleteObjects();

  private:
    int				_layer;
    bool			_physic;
    gameObjectSet		_objects;
    std::stack<GameObject*>	_deletes;
    TimeEffectGroup		*_timeEffectGroup;
};

typedef std::pair<std::string, std::string>	stringPair;
typedef	std::map<stringPair, Callback*>		collisionGroupsMap;
typedef std::map<std::string, Group*>		groupsMap;
typedef std::multimap<int, Group*>		groupsDisplay;

class GameObjectManager
{
  public:
    GameObjectManager();

    virtual ~GameObjectManager();
    bool	existingGroup(const std::string &group) const;
    bool	collisionGroups(const std::string &group1,
		const std::string &group2, bool reverse = true) const;
    void	addGroup(const std::string &group, int layer = 1,
		    	 std::string const &timeEffectGroup = "default");
    void	addGameObject(GameObject *object, const std::string &group, int layer = 1);
    void	removeGameObject(GameObject *object);
    template <class InstanceClass>
    void	setCollisionGroups(const std::string &group1, const std::string &group2,
		void (InstanceClass::*function)(GameObject&));
    void	setGroup(const std::string &name, int layer,
		    	 bool physic, std::string const &timeEffectGroup);
    void	drawGameObject(double elapseTime) const;

    // getter
    collisionGroupsMap const	&getCollisionGroups() const;
    groupsMap const		&getGroups() const;

  protected:
    collisionGroupsMap		_collisionGroups;
    groupsMap			_groups;
    groupsDisplay		_display;
};

#include "GameObjectManager.ipp"

#endif		/* _GAMEOBJECTMANAGER_ */
