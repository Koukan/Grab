#pragma once

#include <string>
#include "Net.hpp"

class Command : public Net::PoolObject
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
