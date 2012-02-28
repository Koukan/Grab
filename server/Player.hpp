#pragma once

#include "Net.hpp"
#include "GameLogic.hpp"
#include "PacketType.hpp"

class Game;
class Ship;

class Player
{
  public:
    Player(uint8_t id);
    virtual ~Player();
	uint32_t			getId() const;
	Ship				*getShip() const;
	void				setShip(Ship *ship);

  private:
	uint8_t			_id;
	Ship			*_ship;
};
