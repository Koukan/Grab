#pragma once

#include "Command.hpp"
#include "Client.hpp"

class ResourceCommand : public Core::Command
{
  public:
	ResourceCommand(std::string const &nameCommand, uint8_t type = 0,
		uint32_t id = 0, std::string const &name = "", Client *client = 0)
	  : Core::Command(nameCommand), type(type), id(id), name(name), client(client)
	{}
	virtual ~ResourceCommand()
	{}

	uint8_t		type;
	uint32_t	id;
	std::string	name;
	Client		*client;
};
