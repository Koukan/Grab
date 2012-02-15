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
      JOYSTICK4,
	  DEFAULT
    };

  static bool isLeftPressed(Player::type type, InputCommand const &cmd);
  static bool isLeftReleased(Player::type type, InputCommand const &cmd);
  static bool isRightPressed(Player::type type, InputCommand const &cmd);
  static bool isRightReleased(Player::type type, InputCommand const &cmd);
  static bool isUpPressed(Player::type type, InputCommand const &cmd);
  static bool isUpReleased(Player::type type, InputCommand const &cmd);
  static bool isDownPressed(Player::type type, InputCommand const &cmd);
  static bool isDownReleased(Player::type type, InputCommand const &cmd);
};

CORE_END_NAMESPACE
