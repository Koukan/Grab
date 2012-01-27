#pragma once

#include "Command.hpp"
#include "Game.hpp"

class GameCommand : public Command
{
  public:
    GameCommand(std::string const &name) : Command(name),
		idObject(0), idResource(0), x(0), y(0), vx(0), vy(0),
		player(0), game(0)
		{}
    virtual ~GameCommand(){}

	uint32_t			idObject;
	uint32_t			idResource;
	int16_t				x;
	int16_t				y;
	int16_t				vx;
	int16_t				vy;
	Player				*player;
	Game				*game;
};

