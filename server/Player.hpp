#pragma once

#include "Net.hpp"
#include "GameLogic.hpp"
#include "PacketType.hpp"
#include "ShipInfo.hpp"

class Game;
class Ship;
class Client;

class Player
{
  public:
    Player(uint8_t id, Client &client);
    virtual ~Player();

	//getter
	uint32_t					getId() const;
	Ship						*getShip() const;
	bool						isReady() const;
	int							getShipType() const;
	ShipInfo::ShipInfo const	*getShipInfo() const;
	Client						&getClient() const;
	int							getLife() const;

	//setter
	void				setShip(Ship *ship);
	void				setReady(bool ready);
	void				setShipType(int type);
	void				setShipInfo(ShipInfo::ShipInfo const *info);
	void				setLife(int life);
	void				die();
	void				respawn();

  private:
	int							_life;
	uint8_t						_id;
	Client						&_client;
	bool						_ready;
	int							_shipType;
	ShipInfo::ShipInfo const	*_shipInfo;
	Ship						*_ship;
};
