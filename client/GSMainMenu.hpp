#pragma once

#include "GameState.hpp"
#include "Sound.hpp"

class GSMainMenu : public Core::GameState
{
public:
  GSMainMenu();
  ~GSMainMenu();

  void	onStart();
  void	onChange();
  void	onResume();

  void	modeSelection();
  void	joinGame();
  void	options();
  void	quitGame();
};
