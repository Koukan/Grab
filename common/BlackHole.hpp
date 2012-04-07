#pragma once

#include "ConcreteObject.hpp"
#include "GameState.hpp"

class BlackHole : public ConcreteObject
{
public:
	BlackHole(double x, double y, Core::GameState &gameState);
	~BlackHole();

	virtual void draw(double);

private:

};