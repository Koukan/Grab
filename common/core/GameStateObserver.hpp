#pragma once

#include <list>
#include <cstdlib>
#include "Module.hpp"
#include "GameState.hpp"
#include "Observer.hpp"
#include "Observable.hpp"

class GameStateObserver : public Module, public Observer<std::list<GameState*> >
{
public:
	virtual ~GameStateObserver();

protected:
	GameStateObserver(std::string const &name);
	virtual void			notified(Observable<std::list<GameState*> > &source,
				   					 std::list<GameState*> &arg);

	std::list<GameState*>	_glist;
};
