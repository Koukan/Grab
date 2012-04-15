#pragma once

#include "SpecialPower.hpp"

class ConcreteObject;

class Shield : public SpecialPower
{
public:
  Shield(Ship& ship, Core::GameState& state);

  virtual void		start();
  virtual void		stop();

private:
  ConcreteObject*	_shield;
};
