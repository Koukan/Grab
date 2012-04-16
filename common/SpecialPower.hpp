#pragma once

class Ship;
namespace Core
{
  class GameState;
}

class SpecialPower
{
public:
  virtual void start() = 0;
  virtual void stop() {}
  virtual void pushTimedCommand(int ms);

protected:
  SpecialPower(Ship& ship, Core::GameState& state);

  Ship&			_ship;
  Core::GameState&	_state;
};
