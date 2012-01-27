#include "GameState.hpp"
#include "InputManager.hpp"

InputManager::InputManager(GameState &game) : _gs(game), _flush(false) 
{
}

InputManager::~InputManager()
{
  this->_gs.removeHandler(*this);
}

void    InputManager::handleInput(const InputCommand &ev)
{
  InputMap::iterator res = _inputCallbacks.find(ev.Type);

  if (res == _inputCallbacks.end())
    return ;
  for (std::list<CallbackElem*>::iterator it = (*res).second.begin();
		  it != (*res).second.end(); it++)
  {
    if ((*it)->key == -1)
      (*it)->callback->call(ev);
	else if ((ev.Type == InputCommand::KeyPressed || ev.Type == InputCommand::KeyReleased) && (*it)->key == ev.Key.Code)
		(*it)->callback->call(ev);
	else if ((ev.Type == InputCommand::MouseButtonPressed || ev.Type == InputCommand::MouseButtonReleased) && (*it)->key == ev.MouseButton.Button)
		(*it)->callback->call(ev);
	else if ((ev.Type == InputCommand::JoystickButtonPressed || ev.Type == InputCommand::JoystickButtonReleased) && (*it)->key == (int)ev.JoystickButton.Button)
		(*it)->callback->call(ev);
    if (_flush == true)
    {
      _flush = false;
      return ;
    }
  }
}

void		InputManager::flushInput()
{
  std::list<CallbackElem*>::iterator	it;

  for (InputMap::iterator map = _inputCallbacks.begin(); map != _inputCallbacks.end(); map++)
  {
    for (it = map->second.begin(); it != map->second.end() ; it++)
    {
      delete (*it)->callback;
      delete (*it);
    }
  }
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
