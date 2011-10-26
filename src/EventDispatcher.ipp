template <class InstanceClass>
void		EventDispatcher::registerEvent(std::string const &type,
		InstanceClass &instance, void (InstanceClass::*method)(Event &))
{
  _registeredEvents[type].push_back(new Callback(instance, method));
}
