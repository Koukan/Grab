#pragma once

#include "Client.hpp"
#include "Module.hpp"
#include "GameLogic.hpp"
#include "Net.hpp"
#include "Player.hpp"
#include "Modes.hpp"

class Game : public Core::Module
{
  public:
    Game(uint16_t id, uint8_t maxPlayers, Modes::Mode type, std::string const &map);
    virtual ~Game();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	void			updateGameState(double elapsedTime);
	bool			addClient(Client &client);
	void			removeClient(Client &client);
	Player			*addPlayer(Client &client);
	void			removePlayer(int i);
	size_t			nbPlayers() const;
	void			changePlayersStatus(int nb, int ship, bool ready);
	void			loadGame();
	void			ready();

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
	Modes::Mode			_type;
	std::string			_map;
	size_t				_readyPlayers;
	uint8_t				_nbPlayers;
	std::list<Client*>	_clients;
	Player				*_players[4];
	Net::Mutex			_mutex;
	friend class GameLogic;
};
