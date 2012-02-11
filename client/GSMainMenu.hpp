#pragma once

#include "GameState.hpp"

class GSMainMenu : public GameState
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
