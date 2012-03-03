#pragma once

#include "Input.hpp"
#include "Ship.hpp"

class Player
{
public:
  enum type
    {
      KEYBOARD = 0,
      JOYSTICK1,
      JOYSTICK2,
      JOYSTICK3,
      JOYSTICK4,
	  ONLINE
    };

  enum Action
  {
	  FIRE = 0,
	  SPECIAL_FIRE,
	  GRAB1,
	  GRAB2,
	  GRAB3,
	  GRAB4,
	  PAUSE,
	  NBACTIONS
  };

  Player(Player::type type, Ship *ship = 0);
  ~Player();

  //setter
  void					setType(Player::type type);
  void					setShip(Ship *ship);
  void					setShipInfo(Ship::ShipInfo const *info);

  //getter
  Player::type			getType() const;
  Ship					*getShip() const;
  Ship::ShipInfo const	*getShipInfo() const;
  Core::InputCommand	&getAction(Player::Action action);

private:
	Player::type			_type;
	Core::InputCommand		_actions[NBACTIONS];
	Ship					*_ship;
	Ship::ShipInfo const	*_shipInfo;
};
