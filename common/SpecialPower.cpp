#include "SpecialPower.hpp"
#include "GameCommand.hpp"
#include "CommandDispatcher.hpp"
#include "Ship.hpp"

SpecialPower::SpecialPower(Ship& ship, Core::GameState& state)
  : _ship(ship), _state(state)
{}

void	SpecialPower::pushTimedCommand(int ms)
{
  GameCommand* cmd = new GameCommand("disableSpecialPower");
  cmd->player = &this->_ship.getPlayer();
  Core::CommandDispatcher::get().pushCommand(*cmd, ms);
}
