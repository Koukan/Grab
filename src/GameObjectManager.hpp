#ifndef		_GAMEOBJECTMANAGER_
#define 	_GAMEOBJECTMANAGER_

#include <map>
#include <set>
#include <string>
#include "Callback.hpp"

class GameObject;

typedef std::set<GameObject*>	gameObjectSet;

class Group
{
  enum
  {
    PHYSIC = 1,
    DRAWABLE = 2
  };

  public:
    Group();
    ~Group();
    void			setFlags(int flags);
    void			setFlags(bool physic, bool drawable);
    void			addObject(GameObject *object);
    void			removeObject(GameObject *object);

    bool			physic;
    bool			drawable;
    gameObjectSet 		objects;
};

typedef std::pair<std::string, std::string>	stringPair;
typedef	std::map<stringPair, Callback*>		relatedGroupsMap;
typedef std::map<std::string, Group>		groupsMap;

class GameObjectManager
{
  public:
    GameObjectManager();
    virtual ~GameObjectManager();
    bool	existingGroup(const std::string &group) const;
    bool	relatedGroups(const std::string &group1,
		const std::string &group2, bool reverse = true) const;
    void	addGroup(const std::string &group);
    void	addGameObject(GameObject *object, const std::string &group);
    void	setRelatedGroups(const std::string &group1,
		const std::string &group2,
		void (*function)(GameObject&, GameObject&));
    template <class InstanceClass>
    void	setRelatedGroups(const std::string &group1,
		const std::string &group2, InstanceClass *instance,
		void (InstanceClass::*function)(GameObject&, GameObject&));
    void	setGroup(const std::string &name, int flags);

  protected:
    relatedGroupsMap	_relatedGroups;
    groupsMap		_groups;
};

#include "GameObjectManager.ipp"

#endif		/* _GAMEOBJECTMANAGER_ */
