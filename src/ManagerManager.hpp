#pragma once
#include <list>
#include "Manager.hpp"

class ManagerManager
{
public:
	ManagerManager(void);
	~ManagerManager(void);

	void	updateManager(GameState &state, int elapsedTime);
	void	loadManager(Manager *manager);
	void	unloadManager(Manager *manager);


protected:
	std::list<Manager*>	_managers;
};
