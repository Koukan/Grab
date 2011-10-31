#pragma once
#include <list>
#include "Manager.hpp"

class ManagerManager : public Manager
{
public:
	ManagerManager(void);
	~ManagerManager(void);

	void	update(GameState &state, int elapsedTime);
	void	loadManager(Manager *manager);
	void	unloadManager(Manager *manager);


protected:
	std::list<Manager*>	_managers;
};
