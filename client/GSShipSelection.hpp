#pragma once

#include "GameState.hpp"
#include "GUIElement.hpp"
#include "Player.hpp"
#include "Modes.hpp"
#include <list>

class GSShipSelection : public Core::GameState
{
public:
  GSShipSelection(std::list<Core::Player *> const *players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online);
  ~GSShipSelection();

  void onStart();
  void back();

  void shipChange(Core::GUIElement const &);

private:
  std::list<Core::Player *> const	*_players;
  Modes::Mode						_mode;
  std::string						_map;
  unsigned int						_nbPlayers;
  bool								_online;
};
