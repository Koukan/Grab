#include "Player.hpp"

bool Player::isLeftPressed(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::X &&
	  cmd.JoystickMove.Position < -0.9f);
}

bool Player::isLeftReleased(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::X &&
	  cmd.JoystickMove.Position > -0.9f);
}

bool Player::isRightPressed(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::X &&
	  cmd.JoystickMove.Position > 0.9f);
}

bool Player::isRightReleased(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::X &&
	  cmd.JoystickMove.Position < 0.9f);
}

bool Player::isUpPressed(Player::type type, InputCommand const &cmd)
{
  if (cmd.Type == InputCommand::JoystickMoved)
    std::cout << "joy move" << std::endl;
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::Y &&
	  cmd.JoystickMove.Position < -0.9f);
}

bool Player::isUpReleased(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::Y &&
	  cmd.JoystickMove.Position > -0.9f);
}

bool Player::isDownPressed(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::Y &&
	  cmd.JoystickMove.Position > 0.9f);
}

bool Player::isDownReleased(Player::type type, InputCommand const &cmd)
{
  return (cmd.Type == InputCommand::JoystickMoved && type > 1 &&
	  static_cast<int>(cmd.JoystickMove.JoystickId) == type - 1 &&
	  cmd.JoystickMove.Axis == Joystick::Axis::Y &&
	  cmd.JoystickMove.Position < 0.9f);
}
