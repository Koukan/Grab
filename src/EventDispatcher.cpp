#include "EventDispatcher.hpp"
#include <iostream>

EventDispatcher::EventDispatcher()
{
  _slow = 1;
}

EventDispatcher::~EventDispatcher()
{
}

void		EventDispatcher::dispatchEvent(double elapsedTime)
{
  _time += elapsedTime;
  dispatch();
  dispatchTimed(_timedEvents, _time);
}

void		EventDispatcher::pushEvent(Event *event)
{
  _events.push(event);
}

void		EventDispatcher::pushEvent(Event *event, int ms, bool relatif)
{
  unsigned int	time;

  //if (relatif)
  //{
    //time = _relativeTime + ms;
    //for (std::list<timedPair>::iterator it = _timedRelativeEvents.begin();
	 //it != _timedRelativeEvents.end(); it++)
    //{
      //if (it->first > time)
      //{
	//_timedRelativeEvents.insert(it, timedPair(time, event));
	//return ;
      //}
    //}
    //_timedRelativeEvents.push_back(timedPair(time, event));
  //}
  //else
  //{
    time = _time + ms;
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
    //}
}

void		EventDispatcher::registerEvent(std::string const &type,
					       void (*function)(Event&))
{
  _registeredEvents[type].push_back(new Callback(function));
}

void		EventDispatcher::removeEvent(std::string const &type)
{
  _registeredEvents.erase(type);
}

void		EventDispatcher::removeSlow()
{
  _slowList.pop_front();
  updateSlow();
}

void		EventDispatcher::setSlow(double slow)
{
  _slowList.push_back(slow);
  updateSlow();
}

double		EventDispatcher::getSlow() const
{
  return _slow;
}

void		EventDispatcher::updateSlow()
{
  if (_slowList.empty())
  {
    _slow = 1;
    return ;
  }

  double	slow = 1000;

  for (std::list<double>::iterator it = _slowList.begin();
       it != _slowList.end(); it++)
  {
    if (*it < slow)
      slow = *it;
  }
  _slow = slow;
}

void		EventDispatcher::dispatch()
{
  eventMap::iterator	it;

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

void		EventDispatcher::dispatchTimed(std::list<timedPair> &list,
					       unsigned int time)
{
  if (!list.empty())
  {
    std::list<timedPair>::iterator	it = list.begin();
    eventMap::iterator			callback;

    while (it != list.end() && it->first < time)
    {
      callback = _registeredEvents.find(it->second->getType());
      if (callback != _registeredEvents.end())
      {
        for (std::list<Callback*>::iterator callbacks = callback->second.begin();
	     callbacks != callback->second.end(); callbacks++)
      	{
	  (*callbacks)->call(*it->second);
      	}
      }
      delete it->second;
      it = list.erase(it);
    }
  }
}

