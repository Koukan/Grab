#pragma once

#include <list>
#include <string>
#include "GameState.hpp"

class Game;

class GameLogic : public GameState
{
  public:
    GameLogic(Game &game);
    virtual ~GameLogic();
	virtual void		update(double elapsedTime);
	virtual bool		handleCommand(Command const &command);
	Game				&getGame() const;
	void				startGame();

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

	void createEnnemies(double elapseTime);
	Game				&_game;
	int					_nbEnemies;
	double				_elapseTime;
	bool				_gameStarted;
};
