#pragma once

#include <string>
#include "GameState.hpp"

class GSPauseMenu : public Core::GameState
{
public:
  GSPauseMenu();
  ~GSPauseMenu();

  void	returnMainMenu();
  void	resumeGame();
  void	onStart();

private:
  std::string	_nbPlayers;
};
