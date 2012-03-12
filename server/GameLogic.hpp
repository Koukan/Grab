#pragma once

#include <list>
#include <string>
#include "GameState.hpp"

class Game;

class GameLogic : public Core::GameState
{
  public:
    GameLogic(Game &game);
    virtual ~GameLogic();
	virtual void		update(double elapsedTime);
	virtual bool		handleCommand(Core::Command const &command);
	Game				&getGame() const;
	void				startGame();
	uint32_t			getSeed() const;

  private:
  enum SalvoType
  {
	  SIMPLE = 0,
	  SINUSOIDAL,
	  BOMB,
	  RANDOM,
	  WALL
  };

  struct	Boss
  {
	  std::string	bulletName;
	  int			life;
  };

  struct	Salvo
  {
	  SalvoType type;
	  int		nbEnemies;
	  std::string bulletName;
	  int		occurenceFrequency;
  };

	Game				&_game;
	int					_nbEnemies;
	double				_elapseTime;
	bool				_gameStarted;
	Net::MTRand			_rand;
};
