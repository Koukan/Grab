#include "Game.hpp"
#include "GameStateManager.hpp"
#include "RendererManager.hpp"
#include "InputManager.hpp"

InputManager::InputManager() : _flush(false)
{
}

InputManager::~InputManager()
{
	//this->flushInput();
}

void		InputManager::handleInput(const CL_InputEvent &event, const CL_InputState &state)
{
  InputMap::iterator res = _inputCallbacks.find(event.type);

  if (res == _inputCallbacks.end())
    return ;
  for (std::list<CallbackElem*>::iterator it = (*res).second.begin();
		  it != (*res).second.end(); it++)
  {
    if (((*it)->inputType == event.device.get_type() ||
     (*it)->inputType == CL_InputDevice::unknown)
     && ((*it)->key == event.id || (*it)->key == -1))
    {
      (*it)->callback->call(event);
      if (_flush == true)
      {
        _flush = false;
        return ;
      }
    }
  }
}

void		InputManager::unmapInput(CL_InputEvent::Type eventType, CL_InputDevice::Type inputType, int key)
{
  InputMap::iterator res = _inputCallbacks.find(eventType);

  if (res ==  _inputCallbacks.end())
    return ;
  for (std::list<CallbackElem*>::iterator it = (*res).second.begin();
		  it != (*res).second.end(); it++)
  {
    if (((*it)->inputType == inputType ||
     (inputType == CL_InputDevice::unknown))
     && ((*it)->key == key || key == -1))
    {
		(*res).second.erase(it);
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

