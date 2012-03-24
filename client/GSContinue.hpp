#pragma once

#include "GameState.hpp"

class GSContinue : public Core::GameState
{
public:
  GSContinue();
  ~GSContinue();
  virtual void onStart();
  virtual void update(double elapsedTime);

  void	returnToGame(Core::InputCommand const &cmd);

private:
  int				_time;
  bool				_continue;
  Core::CoreFont*	_timer;
};
