#pragma once

#include <string>
#include "GameState.hpp"
#include "Modes.hpp"

class GSPartySettings : public GameState
{
public:
  GSPartySettings(Modes::Mode mode, std::string const &map = "");
  ~GSPartySettings();

  void  nbPlayerList(std::string const &nbPlayer);
  void	multiMode(std::string const &mode);

  void	createParty();
  void	back();
  void	onStart();

private:
  std::string	_nbPlayers;
  Modes::Mode	_mode;
  std::string	_map;
  bool		_online;
};
