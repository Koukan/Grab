#pragma once

#include <string>
#include "Modes.hpp"
#include "GameState.hpp"
#include "Player.hpp"

class GSGameOver : public Core::GameState
{
public:
  GSGameOver(bool victory, std::list<Player *> const& players, Modes::Mode mode,
	     std::string const& map, unsigned int nbPlayers, bool online);

  virtual ~GSGameOver();
  virtual void onStart();
  virtual void onEnd();
  virtual bool	handleCommand(Core::Command const &command);
  void		retry();
  void		returnToMainMenu();

private:
  bool		_victory;
  std::list<Player *> const& _players;
  Modes::Mode	_mode;
  std::string const& _map;
  unsigned int _nbPlayers;
  bool		_online;
};
