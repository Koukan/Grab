#pragma once

#include <string>
#include <list>
#include "GameState.hpp"
#include "Modes.hpp"

class Player;
class GSInGame;

class GSPauseMenu : public Core::GameState
{
public:
  GSPauseMenu(GSInGame &inGame, std::list<Player *>& players,
	      Modes::Mode mode, std::string const& map, 
	      unsigned int nbPlayers, bool online);
  ~GSPauseMenu();

  virtual void	onStart();
  virtual bool	handleCommand(Core::Command const &cmd);
  void			returnMainMenu();
  void			resumeGame();
  void			reBind();
  void			changeMap();
  void			retry();

private:
  GSInGame				&_inGame;
  std::list<Player *>&	_players;
  Modes::Mode			_mode;
  std::string const&	_map;
  unsigned int			_nbPlayers;
  bool					_online;
};
