#pragma once

#include "Net.hpp"
#include "Game.hpp"

class GameTask : public Net::Task
{
  public:
    GameTask(Game &game, double elapsedTime);
    virtual ~GameTask();
	virtual void	operator()();

  private:
	Game			&_game;
	double			_elapsedTime;
};
