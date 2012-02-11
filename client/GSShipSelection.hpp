#pragma once

#include "GameState.hpp"

class GSShipSelection : public GameState
{
public:
  GSShipSelection(unsigned int nbPlayers, bool online);
  ~GSShipSelection();

  void onStart();
  void back();

private:
  unsigned int _nbPlayers;
  bool	       _online;
};
