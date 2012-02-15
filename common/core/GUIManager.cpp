#include "GUIManager.hpp"

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
  {
	  GUICommand *cmd = this->createGUICommand(static_cast<InputCommand const &>(command));
	  if (!cmd)
		  return (false);
	  bool ret = this->handleGUICommand(*cmd);
	  delete cmd;
	  return (ret);
  }
  return (false);
}

GUICommand *GUIManager::createGUICommand(InputCommand const &cmd)
{
	GUICommand *command = 0;
	GUICommand::ButtonAction buttonAction;

	if (cmd.Type == InputCommand::KeyPressed || cmd.Type == InputCommand::KeyReleased)
	{
		if (cmd.Type == InputCommand::KeyPressed)
			buttonAction = GUICommand::PRESSED;
		else
			buttonAction = GUICommand::RELEASED;
		if (cmd.Key.Code == Keyboard::Return)
			command = new GUICommand(GUIManager::KEYBOARD, GUICommand::SELECT, buttonAction);
		else if (cmd.Key.Code == Keyboard::Up)
			command = new GUICommand(GUIManager::KEYBOARD, GUICommand::UP, buttonAction);
		else if (cmd.Key.Code == Keyboard::Down)
			command = new GUICommand(GUIManager::KEYBOARD, GUICommand::DOWN, buttonAction);
		else if (cmd.Key.Code == Keyboard::Left)
			command = new GUICommand(GUIManager::KEYBOARD, GUICommand::LEFT, buttonAction);
		else if (cmd.Key.Code == Keyboard::Right)
			command = new GUICommand(GUIManager::KEYBOARD, GUICommand::RIGHT, buttonAction);
		else
			command = new GUICommand(GUIManager::KEYBOARD, cmd.Key.Code, buttonAction);
	}
	else if (cmd.Type == InputCommand::JoystickMoved)
	{
		if (cmd.JoystickMove.Position < -99.f)
		{
			if (cmd.JoystickMove.Axis == Joystick::X)
				command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::LEFT, GUICommand::PRESSED);
			else if (cmd.JoystickMove.Axis == Joystick::Y)
				command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::UP, GUICommand::PRESSED);
		}
		else if (cmd.JoystickMove.Position > 99.f)
		{
			if (cmd.JoystickMove.Axis == Joystick::X)
				command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::RIGHT, GUICommand::PRESSED);
			else if (cmd.JoystickMove.Axis == Joystick::Y)
				command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::DOWN, GUICommand::PRESSED);
		}
	}
	else if (cmd.Type == InputCommand::JoystickButtonPressed)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::PRESSED);
	}
	else if (cmd.Type == InputCommand::JoystickButtonReleased)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::RELEASED);
	}
	return (command);
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
      GUICommand::DirectionState &direction = this->_direction[cmd.JoystickMove.JoystickId + 1];

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
      GUICommand::DirectionState &direction = this->_direction[0];

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
      GUICommand::DirectionState &direction = this->_direction[0];

      if (cmd.Key.Code == Keyboard::Left ||
	  cmd.Key.Code == Keyboard::Right ||
	  cmd.Key.Code == Keyboard::Up ||
	  cmd.Key.Code == Keyboard::Down)
	direction = GUICommand::DEFAULT;
    }
  return (true);
}
