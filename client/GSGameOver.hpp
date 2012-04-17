#pragma once

#include <string>
#include "Modes.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Font.hpp"

class GSGameOver : public Core::GameState
{
public:
  GSGameOver(bool victory, std::list<Player *>& players, Modes::Mode mode,
	     std::string const& map, unsigned int nbPlayers, bool online);

  virtual		~GSGameOver();
  virtual void		onStart();
  virtual bool		handleCommand(Core::Command const &command);
  void			retry();
  void			returnToMainMenu();
  void			reBind();
  void			changeMap();

private:
  bool			_victory;
  std::list<Player *>&	_players;
  Modes::Mode		_mode;
  std::string const&	_map;
  unsigned int		_nbPlayers;
  bool			_online;
  Core::CoreFont*	_state;

  void			coopMode();
  void			oneWinnerMode();
  void			displayScore(Core::Sprite* sprite, Core::Sprite* aura,
				     Ship* ship, Core::CoreFont* score,
				     unsigned int x, unsigned int y);
};
