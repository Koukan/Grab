#ifndef		_PHYSICMANAGER_
#define 	_PHYSICMANAGER_

#include "GameState.hpp"
#include "PhysicObject.hpp"
#include "GameStateObserver.hpp"
#include "Singleton.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ PhysicManager : public GameStateObserver
{
  public:
    PhysicManager();
    virtual ~PhysicManager();
	virtual void	init();
    virtual void	update(double elapsedTime);
	virtual void	destroy();
	static void		apply(GameState &state, double elapsedTime);
	virtual void	notified(Observable<std::list<GameState*> > &source,
				   			 std::list<GameState*> &arg);

  private:
    static void		move(GameObjectManager::groupsMap const &, double);
    static void		collide(GameObjectManager::groupsMap const&,
							GameObjectManager::collisionGroupsMap const&);

	bool					_notified;
	std::list<GameState*>	_list;
};

CORE_END_NAMESPACE

#endif		/* _PHYSICMANAGER_ */
