#pragma once
#include "GameState.hpp"

class Manager
{
public:
	Manager(void) {}
	virtual ~Manager(void) {}

	virtual void	update(GameState &state, double elapsedTime) = 0;
};
