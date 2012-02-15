#pragma once

#include "Command.hpp"
#include "Player.hpp"

class ResourceCommand : public Command
{
  public:
	ResourceCommand(std::string const &nameCommand, uint8_t type = 0,
		uint32_t id = 0, std::string const &name = "", Player *player = 0)
		: Command(nameCommand), type(type), id(id), name(name), player(player)
	{}
	virtual ~ResourceCommand()
	{}

	uint8_t		type;
	uint32_t	id;
	std::string	name;
	Player		*player;
};
