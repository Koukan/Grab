#ifndef		_PHYSICMANAGER_
#define 	_PHYSICMANAGER_

#include "GameState.hpp"
#include "PhysicObject.hpp"

class PhysicManager
{
  public:
    PhysicManager();
    virtual ~PhysicManager();
    void		update(const GameState &);
};

#endif		/* _PHYSICMANAGER_ */
