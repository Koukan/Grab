#pragma once

#include "Net.hpp"
#include "GameLogic.hpp"
#include "PacketType.hpp"

class Game;
class Ship;
class Client;

class Player
{
  public:
    Player(uint8_t id, Client &client);
    virtual ~Player();

	//getter
	uint32_t			getId() const;
	Ship				*getShip() const;
	bool				isReady() const;
	int					getShipType() const;
	Client				&getClient() const;

	//setter
	void				setShip(Ship *ship);
	void				setReady(bool ready);
	void				setShipType(int type);

  private:
	uint8_t			_id;
	Client			&_client;
	bool			_ready;
	int				_shipType;
	Ship			*_ship;
};
