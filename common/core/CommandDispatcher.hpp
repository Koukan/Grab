#pragma once

#include <queue>
#include "Singleton.hpp"
#include "Module.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ CommandDispatcher : public Module, public Net::Singleton<CommandDispatcher>
{
  public:
    CommandDispatcher();
    virtual ~CommandDispatcher();
	virtual void		init();
	virtual void		update(double elapsedTime = 0);
	virtual void		destroy();
};

CORE_END_NAMESPACE
