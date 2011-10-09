#include "EventDispatcher.hpp"
#include <iostream>

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
  int		time = _clock.getElapsedTime() + ms;

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
  _registeredEvents[type].push_back(new Callback(function));
}

void		EventDispatcher::removeEvent(std::string type)
{
  _registeredEvents.erase(type);
}

void		EventDispatcher::dispatch(void)
{
  std::map<std::string, std::list<Callback*> >::iterator	it;

  while (!_events.empty())
  {
    it = _registeredEvents.find(_events.front()->getType());
    if (it != _registeredEvents.end())
    {
      for (std::list<Callback*>::iterator callbacks = it->second.begin(); callbacks != it->second.end(); callbacks++)
      {
        (*callbacks)->call(_events.front());
      }
    }
    delete _events.front();
    _events.pop();
  }
}

void		EventDispatcher::dispatchTimed(void)
{
  if (!_timedEvents.empty())
  {
    std::list<timedPair>::iterator	it = _timedEvents.begin();
    std::map<std::string, std::list<Callback*> >::iterator    callback;
    int		time = _clock.getElapsedTime();
    while (it != _timedEvents.end() && it->first < time)
    {
      callback = _registeredEvents.find(it->second->getType());
      if (callback != _registeredEvents.end())
      {
        for (std::list<Callback*>::iterator callbacks = callback->second.begin(); callbacks != callback->second.end(); callbacks++)
      	{
		(*callbacks)->call(it->second);
      	}
      }
      delete it->second;
      it = _timedEvents.erase(it);
    }
  }
}
