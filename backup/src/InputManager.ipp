template <typename T>
void		InputManager::registerInputCallback(CL_InputEvent::Type eventType,
		T &instance, void (T::*method)(const CL_InputEvent &event), CL_InputDevice::Type inputType, int key)
{
  if (!method)
    return ;
  CallbackElem	*tmp = new CallbackElem();
  tmp->eventType = eventType;
  tmp->inputType = inputType;
  tmp->key = key;
  tmp->callback = new Callback(instance, method);
  _inputCallbacks[eventType].push_back(tmp);
}
