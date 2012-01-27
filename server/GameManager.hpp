#pragma once

#include "Game.hpp"
#include "Net.hpp"

class GameManager
{
  public:
	typedef	std::map<uint16_t, Game*>	gamesMap;
    GameManager();
    virtual ~GameManager();
	Game			*getGame(uint16_t id);
	Game			*createGame(uint8_t maxPlayers = 4);
	gamesMap const	&getGameList() const;
	void			removeGame(uint16_t id);
	bool			gameExist(Game *game);
	void			unlock();

  private:
	uint16_t				_id;
	gamesMap				_games;
	mutable Net::Mutex		_mutex;
};
