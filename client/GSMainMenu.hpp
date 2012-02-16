#pragma once

#include "GameState.hpp"

class GSMainMenu : public Core::GameState
{
public:
  GSMainMenu();
  ~GSMainMenu();

  void	onStart();

  void	modeSelection();
  void	inGameTest();
  void	joinGame();
  void	options();
  void	quitGame();
};
