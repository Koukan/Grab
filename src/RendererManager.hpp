#pragma once

#include "Manager.hpp"

class GameObjectManager;

class RendererManager : public Manager
{
public:
	RendererManager(void);
	~RendererManager(void);

	void update(GameState &state, int elapsedTime);
};

