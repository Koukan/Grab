#pragma once

#include <string>
#include <list>
#include "GameState.hpp"
#include "Modes.hpp"

class Player;

class GSPauseMenu : public Core::GameState
{
public:
  GSPauseMenu(std::list<Player *>& players,
	      Modes::Mode mode, std::string const& map, 
	      unsigned int nbPlayers, bool online);
  ~GSPauseMenu();

  void	returnMainMenu();
  void	resumeGame();
  void	onStart();
  void	retry();

private:
  std::list<Player *>&	_players;
  Modes::Mode		_mode;
  std::string const&	_map;
  unsigned int		_nbPlayers;
  bool			_online;
};
