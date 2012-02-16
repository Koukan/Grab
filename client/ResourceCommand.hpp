#pragma once

#include "Command.hpp"

class ResourceCommand : public Core::Command
{
  public:
	ResourceCommand(std::string const &nameCommand, uint8_t type = 0,
		uint32_t id = 0, std::string const &name = "")
	  : Core::Command(nameCommand), type(type), id(id), name(name)
	{}
	virtual ~ResourceCommand()
	{}

	uint8_t		type;
	uint32_t	id;
	std::string	name;
};
