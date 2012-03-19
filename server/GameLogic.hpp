#pragma once

#include <list>
#include <string>
#include "GameState.hpp"

class Game;
class GameCommand;
class Map;

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

	void				moveCommand(Core::Command const &);
	void				spawnSpawnerCommand(Core::Command const &);
	void				updateCannonCommand(Core::Command const &);
	void				fireStateCommand(Core::Command const &);

	Game				&_game;
	int					_nbEnemies;
	double				_elapseTime;
	bool				_gameStarted;
	Net::MTRand			_rand;
	Map					*_map;
};
