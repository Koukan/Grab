#pragma once

#include "Singleton.hpp"
#include "Module.hpp"

class CommandDispatcher : public Module, public Singleton<CommandDispatcher>
{
  public:
    CommandDispatcher();
    virtual ~CommandDispatcher();
	virtual void		init();
	virtual void		update(double elapsedTime = 0);
	virtual void		destroy();
};
