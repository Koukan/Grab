#pragma once

#include "GameState.hpp"

class GSContinue : public Core::GameState
{
public:
  GSContinue();
  virtual ~GSGameOver();
  virtual void onStart();

};
