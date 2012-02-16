#pragma once

#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ Task
{
  public:
    Task(){}
    virtual ~Task(){}
	virtual void	operator()() = 0;
};

NET_END_NAMESPACE
