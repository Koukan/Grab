#include "GUIManager.hpp"
#include "Game.hpp"

GUIManager::GUIManager()
  : GUILayout(0, 0, 0, 0, 0, 0, 0)
{
}

GUIManager::~GUIManager()
{
	for (std::list<ButtonSprite *>::iterator it = this->_spriteButtons.begin(); it != this->_spriteButtons.end(); ++it)
	{
		delete *it;
	}
}

bool		GUIManager::handleCommand(Command const &command)
{
  if (command.name == "Input" && this->updateDirection(static_cast<InputCommand const &>(command)))
    return (this->handleGUICommand(static_cast<InputCommand const &>(command)));
  return (false);
}

void		GUIManager::registerButtonSprite(ButtonSprite &sprite)
{
  this->_spriteButtons.push_front(&sprite);
}

void		GUIManager::init()
{
}

void		GUIManager::update(double elapsedTime)
{
}

void		GUIManager::destroy()
{
}

bool		GUIManager::updateDirection(InputCommand const &cmd)
{
  if (cmd.Type == InputCommand::JoystickMoved)
    {
      GUICommand::directionState &direction = this->_direction[cmd.JoystickMove.JoystickId + 1];

      if (cmd.JoystickMove.Axis == Joystick::X)
	{
          if (cmd.JoystickMove.Position < -80.f)
	    direction = GUICommand::LEFT;
	  else if (cmd.JoystickMove.Position > 80.f)
	    direction = GUICommand::RIGHT;
	  else if (cmd.JoystickMove.Position > -10.f && cmd.JoystickMove.Position < 10.f)
	    direction = GUICommand::DEFAULT;
	}
      else if (cmd.JoystickMove.Axis == Joystick::Y)
	{
          if (cmd.JoystickMove.Position < -80.f)
	    direction = GUICommand::UP;
	  else if (cmd.JoystickMove.Position > 80.f)
	    direction = GUICommand::DOWN;
	  else if (cmd.JoystickMove.Position > -10.f && cmd.JoystickMove.Position < 10.f)
	    direction = GUICommand::DEFAULT;
	}
    }
  else if (cmd.Type == InputCommand::KeyPressed)
    {
      GUICommand::directionState &direction = this->_direction[0];

      if (cmd.Key.Code == Keyboard::Left)
	direction = GUICommand::LEFT;
      else if (cmd.Key.Code == Keyboard::Right)
	direction = GUICommand::RIGHT;
      else if (cmd.Key.Code == Keyboard::Up)
	direction = GUICommand::UP;
      else if (cmd.Key.Code == Keyboard::Down)
	direction = GUICommand::DOWN;
    }
  else if (cmd.Type == InputCommand::KeyReleased)
    {
      GUICommand::directionState &direction = this->_direction[0];

      if (cmd.Key.Code == Keyboard::Left ||
	  cmd.Key.Code == Keyboard::Right ||
	  cmd.Key.Code == Keyboard::Up ||
	  cmd.Key.Code == Keyboard::Down)
	direction = GUICommand::DEFAULT;
    }
  return (true);
}
