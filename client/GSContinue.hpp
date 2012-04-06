#pragma once

#include "GameState.hpp"
#include <list>

class GSInGame;
class Player;

class GSContinue : public Core::GameState
{
public:
  GSContinue(GSInGame& inGame, std::list<Player *> const & players);
  ~GSContinue();
  virtual void onStart();
  virtual void update(double elapsedTime);

  void	returnToGame(Core::InputCommand const &cmd);

private:
  int				_time;
  bool				_continue;
  Core::CoreFont*		_timer;
  Core::CoreFont*		_info;
  GSInGame&			_inGame;
  std::list<Player *> const &	_players;
};
