#pragma once

#include "Client.hpp"
#include "Module.hpp"
#include "GameLogic.hpp"
#include "Net.hpp"
#include "Player.hpp"

class Game : public Core::Module
{
  public:
    Game(uint16_t id, uint8_t maxPlayers);
    virtual ~Game();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	void			updateGameState(double elapsedTime);
	bool			addClient(Client &client);
	void			removeClient(Client &client);
	Player			*addPlayer();
	void			removePlayer(int i);
	size_t			nbPlayers() const;

	//getter
	bool						isFull() const;
	uint16_t					getId() const;
	uint8_t						getMaxPlayers() const;
	GameLogic					&getGameLogic();
	std::list<Client*> const	&getClients() const;
	Player	* const 			*getPlayers() const;

  private:
	void			startGame();

	GameLogic			_logic;
	uint16_t			_id;
	uint8_t				_maxPlayers;
	size_t				_readyPlayers;
	uint8_t				_nbPlayers;
	std::list<Client*>	_clients;
	Player				*_players[4];
	Net::Mutex			_mutex;
	friend class GameLogic;
};
