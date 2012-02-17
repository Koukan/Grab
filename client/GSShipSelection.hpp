#pragma once

#include "GameState.hpp"
#include "GUIElement.hpp"

class GSShipSelection : public Core::GameState
{
public:
  GSShipSelection(unsigned int nbPlayers, bool online);
  ~GSShipSelection();

  void onStart();
  void back();

  void shipChange(Core::GUIElement const &);

private:
  unsigned int _nbPlayers;
  bool	       _online;
};
