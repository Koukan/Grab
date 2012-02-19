#include "GUIManager.hpp"
#include "GameStateManager.hpp"

CORE_USE_NAMESPACE

GUIManager::GUIManager()
  : GUILayout(0, 0, 0, 0, 0, 0, 0)
{
	this->_direction[0] = GUICommand::DEFAULT;
	this->_direction[1] = GUICommand::DEFAULT;
	this->_direction[2] = GUICommand::DEFAULT;
	this->_direction[3] = GUICommand::DEFAULT;
	this->_elapsedTime[0] = 0;
	this->_elapsedTime[1] = 0;
	this->_elapsedTime[2] = 0;
	this->_elapsedTime[3] = 0;
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
	  bool ret = this->catchGUICommand(*cmd);
	  delete cmd;
	  return (ret);
  }
  return (false);
}

bool		GUIManager::handleGUICommand(GUICommand const &command)
{
	if (this->GUILayout::handleGUICommand(command))
		return (true);
	if (command.type == Core::GUICommand::ACTION &&
		command.buttonAction == Core::GUICommand::RELEASED &&
		command.action == Core::GUICommand::BACK)
	{
		GameStateManager::get().popState();
		return (true);
	}
	return (false);
}

GUICommand *GUIManager::createGUICommand(InputCommand const &cmd)
{
	GUICommand *command = 0;
	GUICommand::ButtonAction buttonAction;

	if (cmd.Type == InputCommand::JoystickMoved)
	{
		std::cout << "joystick " << cmd.JoystickMove.JoystickId << std::endl;
		std::cout << "axis " << cmd.JoystickMove.Axis << std::endl;
		std::cout << "position " << cmd.JoystickMove.Position << std::endl;
	}
	if (cmd.Type == InputCommand::KeyPressed || cmd.Type == InputCommand::KeyReleased)
	{
		if (cmd.Type == InputCommand::KeyPressed)
			buttonAction = GUICommand::PRESSED;
		else
			buttonAction = GUICommand::RELEASED;
		if (cmd.Key.Code == Keyboard::Return)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::SELECT, buttonAction, cmd.Key.Code);
		else if (cmd.Key.Code == Keyboard::Back)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::BACK, buttonAction, cmd.Key.Code);
		else if (cmd.Key.Code == Keyboard::Up)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::UP, buttonAction, cmd.Key.Code);
		else if (cmd.Key.Code == Keyboard::Down)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::DOWN, buttonAction, cmd.Key.Code);
		else if (cmd.Key.Code == Keyboard::Left)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::LEFT, buttonAction, cmd.Key.Code);
		else if (cmd.Key.Code == Keyboard::Right)
			command = new GUICommand(GUICommand::KEYBOARD, GUICommand::RIGHT, buttonAction, cmd.Key.Code);
		else
			command = new GUICommand(GUICommand::KEYBOARD, cmd.Key.Code, buttonAction, cmd.Key.Code);
	}
	else if (cmd.Type == InputCommand::JoystickMoved)
	{
		if (cmd.JoystickMove.Axis == Joystick::X &&
			(this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::DEFAULT ||
			this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::LEFT ||
			this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::RIGHT))
		{
			if (cmd.JoystickMove.Position < -60.f)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::LEFT;
			else if (cmd.JoystickMove.Position > 60.f)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::RIGHT;
			else
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::DEFAULT;
		}
		else if (cmd.JoystickMove.Axis == Joystick::Y &&
			(this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::DEFAULT ||
			this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::UP ||
			this->_direction[cmd.JoystickMove.JoystickId] == GUICommand::DOWN))
		{
			if (cmd.JoystickMove.Position < -60.f)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::UP;
			else if (cmd.JoystickMove.Position > 60.f)
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::DOWN;
			else
				this->_direction[cmd.JoystickMove.JoystickId] = GUICommand::DEFAULT;
		}
	}
	else if (cmd.Type == InputCommand::JoystickButtonPressed)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::PRESSED, cmd.JoystickButton.Button);
		else if (cmd.JoystickButton.Button == 1)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::BACK, GUICommand::PRESSED, cmd.JoystickButton.Button);
		else
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::UNKNOWN, GUICommand::PRESSED, cmd.JoystickButton.Button);
	}
	else if (cmd.Type == InputCommand::JoystickButtonReleased)
	{
		if (cmd.JoystickButton.Button == 0)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::SELECT, GUICommand::RELEASED, cmd.JoystickButton.Button);
		else if (cmd.JoystickButton.Button == 1)
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::BACK, GUICommand::RELEASED, cmd.JoystickButton.Button);
		else
			command = new GUICommand(static_cast<GUICommand::PlayerType>(cmd.JoystickButton.JoystickId + 1), GUICommand::UNKNOWN, GUICommand::RELEASED, cmd.JoystickButton.Button);
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
	static bool repeat[4] = {false, false, false, false};

	for (int i = 0; i < 4; ++i)
	{
		if (this->_direction[i] != GUICommand::DEFAULT)
		{
			if (this->_elapsedTime[i] <= 0)
			{
				GUICommand *cmd = new GUICommand(static_cast<GUICommand::PlayerType>(i + 1), this->_direction[i], GUICommand::PRESSED, 0);
				this->handleGUICommand(*cmd);
				cmd->buttonAction = GUICommand::RELEASED;
				this->handleGUICommand(*cmd);
				delete cmd;
				if (!repeat[i])
				{
					this->_elapsedTime[i] = 500;
					repeat[i] = true;
				}
				else
					this->_elapsedTime[i] = 50;
			}
			else
				this->_elapsedTime[i] -= elapsedTime;
		}
		else
		{
			this->_elapsedTime[i] = 0;
			repeat[i] = false;
		}
	}
}

void		GUIManager::destroy()
{
}

