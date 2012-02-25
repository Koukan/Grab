#pragma once

#include "Input.hpp"

class Ship;
class Player
{
public:
  enum type
    {
      KEYBOARD = 0,
      JOYSTICK1,
      JOYSTICK2,
      JOYSTICK3,
      JOYSTICK4
    };

  enum Action
  {
	  FIRE = 0,
	  SPECIAL_FIRE,
	  PAUSE,
	  NBACTIONS
  };

  Player(Player::type type, Ship *ship = 0);
  ~Player();

  Player::type getType() const;
  void setType(Player::type type);
  Core::InputCommand &getAction(Player::Action action);

  void	setShip(Ship *ship);
  Ship *getShip() const;

private:
	Player::type _type;
  Core::InputCommand _actions[NBACTIONS];
	Ship*	     _ship;
};
