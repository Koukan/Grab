#pragma once

#include <list>
#include "Command.hpp"

class Game;

class DestroyCommand : public Core::Command
{
  public:
    DestroyCommand(std::string const &str);
    virtual ~DestroyCommand();

	std::list<size_t>		ids;
	Game					*game;
};

