#ifndef		_PHYSICMANAGER_
#define 	_PHYSICMANAGER_

#include "GameState.hpp"
#include "PhysicObject.hpp"
#include "Manager.hpp"
#include "Singleton.hpp"

class PhysicManager : public Manager, public Singleton<PhysicManager>
{
  public:
    PhysicManager();
    virtual ~PhysicManager();
    virtual void	update(GameState &state, double elapsedTime);

  private:
    void		move(groupsMap const&, double);
    void		collide(groupsMap const&, collisionGroupsMap const&);
};

#endif		/* _PHYSICMANAGER_ */
