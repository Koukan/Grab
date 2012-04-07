#include "BlackHole.hpp"
#include "CircleHitBox.hpp"

BlackHole::BlackHole(double x, double y, Core::GameState &gameState)
	: ConcreteObject("blackHole", *(new Core::CircleHitBox(x, y, 500)), 0, 0, -500, -500)
{
	gameState.addGameObject(this, "blackHoles");
}

BlackHole::~BlackHole()
{
}

void BlackHole::draw(double elapsedTime)
{
	this->ConcreteObject::draw(elapsedTime);
}