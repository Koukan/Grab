#pragma once

#include "Client.hpp"
#include "Module.hpp"
#include "GameLogic.hpp"
#include "Net.hpp"

class Game : public Core::Module
{
  public:
    Game(uint16_t id, uint8_t maxClients);
    virtual ~Game();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	void			updateGameState(double elapsedTime);
	bool			addClient(Client &player);
	int				addClient();
	void			removeClient(int i);
	void			removeClient(Client &player);
	size_t			nbClients() const;
	bool			isFull() const;
	uint16_t		getId() const;
	uint8_t			getMaxClients() const;
    void			addReadyClient();
	void			sendTCPPacket(Net::Packet &packet, Client *player = 0);
	void			sendUDPPacket(Net::Packet &packet, Client *player = 0);
	GameLogic		&getGameLogic();
	std::list<Client*> const	&getClients() const;

  private:
	void			broadcastStatus(Client &player, int status);
	void			startGame();

	GameLogic			_logic;
	uint16_t			_id;
	uint8_t				_maxClients;
	size_t				_readyClients;
	std::list<Client*>	_list;
	bool				_test[4]; // a modifier
	Net::Mutex			_mutex;
	friend class GameLogic;
};
