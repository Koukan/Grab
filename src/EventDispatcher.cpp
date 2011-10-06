#include "EventDispatcher.hpp"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void		EventDispatcher::dispatchEvent(void)
{
  dispatch();
  dispatchTimed();
}

void		EventDispatcher::pushEvent(Event *event)
{
  _events.push(event);
}

void		EventDispatcher::pushEvent(Event *event, int ms)
{
  int		time = ms;

  for (std::list<timedPair>::iterator it = _timedEvents.begin();
	it != _timedEvents.end(); it++)
  {
    if (it->first > time)
    {
      _timedEvents.insert(it, timedPair(time, event));
      return ;
    }
  }
  _timedEvents.push_back(timedPair(time, event));
}

void		EventDispatcher::registerEvent(std::string const &type,
					       void (*function)(Event&))
{
  _registeredEvents[type] = new Callback(function);
}

template <class InstanceClass>
void		EventDispatcher::registerEvent(std::string const &type,
		InstanceClass *instance, void (InstanceClass::*method)(Event&))
{
  _registeredEvents[type] = new Callback(instance, method);
}

void		EventDispatcher::removeEvent(std::string type)
{
  _registeredEvents.erase(type);
}

void		EventDispatcher::dispatch(void)
{
  std::map<std::string, Callback*>::iterator	it;

  while (!_events.empty())
  {
    it = _registeredEvents.find(_events.front()->getType());
    if (it != _registeredEvents.end())
      it->second->call(_events.front());
    delete _events.front();
    _events.pop();
  }
}

void		EventDispatcher::dispatchTimed(void)
{
  std::map<std::string, Callback*>::iterator	it;

  while (!_events.empty())
  {
    it = _registeredEvents.find(_timedEvents.front().second->getType());
    if (it != _registeredEvents.end())
      it->second->call(_events.front());
    delete _timedEvents.front().second;
    _timedEvents.pop_front();
  }
}
