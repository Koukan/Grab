#include "Cannon.hpp"
#include "GameStateManager.hpp"

Cannon::Cannon(std::string const &parser, Ship &ship) :
  BulletCommand(parser, Core::GameStateManager::get().getCurrentState(),
		ship.getX(), ship.getY(), ship.getVx(), ship.getVy()), _ship(ship)
{}

Cannon::~Cannon()
{}
