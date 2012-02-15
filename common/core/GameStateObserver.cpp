#include "GameStateObserver.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

GameStateObserver::GameStateObserver(std::string const &name) : Module(name)
{
	GameStateManager::get().registerObserver(*this);
}

GameStateObserver::~GameStateObserver()
{
}

void			GameStateObserver::notified(Observable<std::list<GameState*> > &,
											std::list<GameState*> &arg)
{
	this->_glist = arg;
}
