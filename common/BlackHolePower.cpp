#include "BlackHolePower.hpp"
#include "BlackHole.hpp"
#include "Ship.hpp"

BlackHolePower::BlackHolePower(Ship& ship, Core::GameState& state) :
  SpecialPower(ship, state)
{}

void	BlackHolePower::start()
{
  this->_ship.setSpecialPowerActive(true);
  new BlackHole(_ship.getX(), _ship.getY(), _state, _ship);
}
