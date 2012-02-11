#pragma once

#include "GameState.hpp"

class GSModeSelection : public GameState
{
public:
  GSModeSelection();
  ~GSModeSelection();

  virtual void	onStart();

  void	back();
  void	story();
  void	survivalScoring();
  void	survivalHighlander();
  void	tryAndRetry();
};
