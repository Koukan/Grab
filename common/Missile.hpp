#pragma once

#include "SpecialPower.hpp"
#include "Color.hpp"

class Missile : public SpecialPower
{
public:
  Missile(Ship& ship, Core::GameState& state, Color const & color);
  virtual void	start();

private:
  Color const	   _color;
};
