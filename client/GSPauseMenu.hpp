#pragma once

#include <string>
#include "GameState.hpp"

class GSPauseMenu : public GameState
{
public:
  GSPauseMenu();
  ~GSPauseMenu();

  void	createParty();
  void	returnMainMenu();
  void	resumeGame();
  void	onStart();

private:
  std::string	_nbPlayers;
};
