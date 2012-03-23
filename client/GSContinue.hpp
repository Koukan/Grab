#pragma once

#include "GameState.hpp"

class GSContinue : public Core::GameState
{
public:
  GSContinue();
  ~GSContinue();
  virtual void onStart();

};
