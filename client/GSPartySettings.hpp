#pragma once

#include <string>
#include "GameState.hpp"
#include "Modes.hpp"
#include "GUIElement.hpp"

class GSPartySettings : public Core::GameState
{
public:
  GSPartySettings(Modes::Mode mode);
  ~GSPartySettings();

  void  nbPlayerList(Core::GUIElement &nb);
  void	multiMode(Core::GUIElement &mode);

  void	createParty();
  void	back();
  void	onStart();

private:
  std::string		_nbPlayers;
  Modes::Mode		_mode;
  bool				_online;
  Core::CoreFont	*_error;
  Core::GUIElement	*_playerList;
};
