#pragma once

#include "Command.hpp"
#include "Game.hpp"

class GameCommand : public Command
{
  public:
    GameCommand(std::string const &name, uint32_t idObject = 0,
		uint32_t idResource = 0, int16_t x = 0, int16_t y = 0,
		int16_t vx = 0, int16_t vy = 0, float position = 0) : Command(name),
		idObject(idObject), idResource(idResource), x(x), y(y), vx(vx), vy(vy),
		position(position)
		{}
    virtual ~GameCommand(){}

	uint32_t			idObject;
	uint32_t			idResource;
	int16_t				x;
	int16_t				y;
	int16_t				vx;
	int16_t				vy;
	float				position;

	uint32_t			score;
};

