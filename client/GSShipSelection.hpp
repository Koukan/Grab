#pragma once

#include "GameState.hpp"
#include "GUIElement.hpp"
#include "Player.hpp"
#include "Modes.hpp"
#include "Ship.hpp"
#include <list>

class GSShipSelection : public Core::GameState
{
public:
  GSShipSelection(std::list<Player *> const *players, Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online);
  ~GSShipSelection();

  void onStart();
  void back();

  void changeToInGame();


private:
  std::list<Player *> const			*_players;
  Modes::Mode						_mode;
  std::string						_map;
  unsigned int						_nbPlayers;
  unsigned int						_nbReady;
  bool								_online;
  Ship::ShipInfo	_selectedShips[4];
};
