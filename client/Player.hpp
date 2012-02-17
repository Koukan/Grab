#pragma once

#include "Input.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ Player
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
	  SPECIAL_FIRE
  };

  Player(Player::type type);
  ~Player();

  Player::type getType() const;
  void setType(Player::type type);
  InputCommand &getAction(Player::Action action);

private:
	Player::type _type;
	InputCommand _actions[2];
};

CORE_END_NAMESPACE
