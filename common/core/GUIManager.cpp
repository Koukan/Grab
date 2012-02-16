#include "GUIManager.hpp"

CORE_USE_NAMESPACE

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
  if (command.name == "Input")
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
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::SELECT, buttonAction);
		else if (cmd.Key.Code == Keyboard::Up)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::UP, buttonAction);
		else if (cmd.Key.Code == Keyboard::Down)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::DOWN, buttonAction);
		else if (cmd.Key.Code == Keyboard::Left)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::LEFT, buttonAction);
		else if (cmd.Key.Code == Keyboard::Right)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::RIGHT, buttonAction);
		else
			command = new GUICommand(GUICommand::KEYBOARD, cmd.Key.Code, buttonAction);
	}
	else if (cmd.Type == InputCommand::JoystickMoved)
	{
		if (cmd.JoystickMove.Position < -99.f)
		{
			if (cmd.JoystickMove.Axis == Joystick::X)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::LEFT; /*command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::LEFT, GUICommand::PRESSED);*/
			else if (cmd.JoystickMove.Axis == Joystick::Y)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::UP; /*command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::UP, GUICommand::PRESSED);*/
		}
		else if (cmd.JoystickMove.Position > 99.f)
		{
			if (cmd.JoystickMove.Axis == Joystick::X)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::RIGHT; /*command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::RIGHT, GUICommand::PRESSED);*/
			else if (cmd.JoystickMove.Axis == Joystick::Y)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::DOWN; /*command = new GUICommand(static_cast<GUIManager::PlayerType>(cmd.JoystickMove.JoystickId + 1), GUICommand::DOWN, GUICommand::PRESSED);*/
		}
		else
			this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::DEFAULT;
	}
	else if (cmd.Type == InputCommand::JoystickButtonPressed)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::PRESSED);
	}
	else if (cmd.Type == InputCommand::JoystickButtonReleased)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::RELEASED);
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

