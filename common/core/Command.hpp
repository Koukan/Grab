#pragma once

#include <string>
#include "Net.hpp"
#include "CoreDef.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ Command : public Net::PoolObject
{
  public:
    Command(std::string const &name) : name(name)
	{
	}
    virtual ~Command()
	{
	}

	std::string const		name;
};

CORE_END_NAMESPACE
