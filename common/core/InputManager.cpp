#include "GameState.hpp"
#include "InputManager.hpp"

CORE_USE_NAMESPACE

InputManager::InputManager(GameState &game) : _gs(game), _flush(false)
{
}

InputManager::~InputManager()
{
  this->_gs.removeHandler(*this);
}

void    InputManager::handleInput(const InputCommand &ev)
{
  auto res = _inputCallbacks.find(ev.Type);

  if (res == _inputCallbacks.end())
    return ;
  for (auto it : (*res).second)
  {
    if (it.key == -1 && it.joystickId == -1)
      it.callback(ev);
	if ((ev.Type == InputCommand::KeyPressed || ev.Type == InputCommand::KeyReleased) && (it.key == -1 || it.key == ev.Key.Code))
		it.callback(ev);
	else if ((ev.Type == InputCommand::MouseButtonPressed || ev.Type == InputCommand::MouseButtonReleased) && (it.key == -1 || it.key == ev.MouseButton.Button))
		it.callback(ev);
	else if ((ev.Type == InputCommand::JoystickButtonPressed || ev.Type == InputCommand::JoystickButtonReleased) &&
		(it.joystickId == -1 || it.joystickId == (int)ev.JoystickButton.JoystickId) &&
		(it.key == -1 || it.key == (int)ev.JoystickButton.Button))
		it.callback(ev);
	else if (ev.Type == InputCommand::JoystickMoved &&
		(it.joystickId == -1 || it.joystickId == (int)ev.JoystickMove.JoystickId))
		it.callback(ev);
    if (_flush == true)
    {
      _flush = false;
      return ;
    }
  }
}

void		InputManager::flushInput()
{
  _inputCallbacks.clear();
  _flush = true;
}

bool		InputManager::handleCommand(Command const &cmd)
{
  if (cmd.name == "Input")
  {
	this->handleInput(static_cast<InputCommand const &>(cmd));
    return true;
  }
  return false;
}
