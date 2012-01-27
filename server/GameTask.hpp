#pragma once

#include "Task.hpp"
#include "Game.hpp"

class GameTask : public Task
{
  public:
    GameTask(Game &game, double elapsedTime);
    virtual ~GameTask();
	virtual void	operator()();

  private:
	Game			&_game;
	double			_elapsedTime;
};
