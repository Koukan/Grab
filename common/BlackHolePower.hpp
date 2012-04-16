#pragma once

#include "SpecialPower.hpp"

class BlackHole;

class BlackHolePower : public SpecialPower
{
public:
  BlackHolePower(Ship& ship, Core::GameState& state);
  void start();
};
