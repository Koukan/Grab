#include "InputManager.hpp"

InputManager::InputManager()
{}

InputManager::~InputManager()
{
  this->flushCallbacks();
}

void		InputManager::handleInput(const CL_InputEvent &event, const CL_InputState &state)
{
  InputMap::iterator res = _inputCallbacks.find(event.type);

  if (res ==  _inputCallbacks.end())
    return ;
  for (std::list<CallbackElem*>::iterator it = (*res).second.begin();
		  it != (*res).second.end(); it++)
  {
    if (((*it)->inputType == event.device.get_type() ||
     (*it)->inputType == CL_InputDevice::unknown)
     && ((*it)->key == event.id || (*it)->key == -1))
    {
      (*it)->callback.invoke(event);
    }
  }
}

void		InputManager::registerInputCallback(CL_InputEvent::Type eventType,
		CL_Callback_v1<const CL_InputEvent &>  &callback,
		CL_InputDevice::Type inputType , int key)
{
  CallbackElem	*tmp = new CallbackElem();
  tmp->eventType = eventType;
  tmp->callback = callback;
  tmp->inputType = inputType;
  tmp->key = key;
  _inputCallbacks[eventType].push_back(tmp);
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

void		InputManager::flushCallbacks()
{
	for (InputMap::iterator map = _inputCallbacks.begin();
			map != _inputCallbacks.end(); map++)
	{
		for (std::list<CallbackElem*>::iterator it = (*map).second.begin();
				it != (*map).second.end() ; it++)
			delete (*it);
	}
}
