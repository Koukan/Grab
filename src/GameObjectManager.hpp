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

class GameState;
class GameObjectManager;

typedef std::set<GameObject*>	gameObjectSet;

class Group
{
  public:
    Group(GameState &state, int layer, std::string const &timeEffectGroup,
	  bool physic = false);
    ~Group();

    void	addObject(GameObject *object);
    void	removeObject(GameObject *object);
    void	draw(double elapseTime) const;
    void	addDelete(GameObject *object);
    void	deleteObjects();

    //setter
    void	setLayer(int layer);
    void	setPhysic(bool physicable);
    void	setTimeEffect(double timeEffect);
    void	setTimeEffectGroup(std::string const &timeEffectGroup);
    void	setFlags(int layer, bool physic, std::string const &timeEffectGroup);

    //getter
    bool		getPhysic() const;
    int			getLayer() const;
    double		getTimeEffect() const;
    TimeEffectGroup	*getTimeEffectGroup() const;
    gameObjectSet const	&getObjects() const;

  private:
    GameState			&_gameState;
    int				_layer;
    bool			_physic;
    TimeEffectGroup		*_timeEffectGroup;
    gameObjectSet		_objects;
    std::stack<GameObject*>	_deletes;
};

typedef std::pair<std::string, std::string>		stringPair;
typedef	std::map<stringPair, IPhysicsSubscriber*>	collisionGroupsMap;
typedef std::map<std::string, Group*>			groupsMap;
typedef std::multimap<int, Group*>			groupsDisplay;

class GameObjectManager : public TimeEffectManager
{
  public:
    GameObjectManager();
    virtual ~GameObjectManager();

    void	addGroup(const std::string &group, int layer = 1,
		    	std::string const &timeEffectGroup = "default");
    void	addGameObject(GameObject *object, const std::string &group,
		    	int layer = 1);
    void	removeGameObject(GameObject *object);
    void	drawGameObject() const;

    // setter
    template <class InstanceClass>
    void	setCollisionGroups(const std::string &group1, const std::string &group2,
			void (InstanceClass::*function)(GameObject&));
    void	setGroup(const std::string &name, int layer,
		    	bool physic, std::string const &timeEffectGroup);

    // getter
    collisionGroupsMap const	&getCollisionGroups() const;
    groupsMap const		&getGroups() const;
    bool			existingGroup(const std::string &group) const;
    bool			collisionGroups(const std::string &group1,
				const std::string &group2, bool reverse = true) const;

  protected:
    collisionGroupsMap		_collisionGroups;
    groupsMap			_groups;
    groupsDisplay		_display;
};

#include "GameObjectManager.ipp"

#endif		/* _GAMEOBJECTMANAGER_ */
