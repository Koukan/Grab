#include "ManagerManager.hpp"

ManagerManager::ManagerManager()
{}

ManagerManager::~ManagerManager()
{}

void	ManagerManager::update(GameState &state, double elapsedTime)
{
  for (std::list<Manager*>::iterator it = _managers.begin(); it != _managers.end(); it++)
  {
    (*it)->update(state, elapsedTime);
  }
}

void	ManagerManager::loadManager(Manager *manager)
{
	if (manager)
	  _managers.push_back(manager);
}

void	ManagerManager::unloadManager(Manager *manager)
{
	_managers.remove(manager);
}
