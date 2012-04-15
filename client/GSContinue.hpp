#pragma once

#include "GameState.hpp"
#include <list>

class GSInGame;
class Player;

class GSContinue : public Core::GameState
{
public:
  GSContinue(GSInGame& inGame, std::list<Player *> const & players, unsigned int nbContinues);
  ~GSContinue();
  virtual void	onStart();
  virtual void	update(double elapsedTime);
  virtual bool	handleCommand(Core::Command const &cmd);

  void			returnToGame(Core::InputCommand const &cmd);

private:
  int							_time;
  bool							_continue;
  Core::CoreFont*				_timer;
  Core::CoreFont*				_info;
  Core::CoreFont*				_nbContinues;
  GSInGame&						_inGame;
  std::list<Player *> const &	_players;
};
