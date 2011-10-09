#ifndef		_EVENTDISPATCHER_
#define 	_EVENTDISPATCHER_

#include <map>
#include <list>
#include <queue>
#include <string>
#include "Event.hpp"
#include "Clock.hpp"
#include "Callback.hpp"

typedef std::pair<int, Event*>	timedPair;

class EventDispatcher
{
  public:
    EventDispatcher();
    virtual ~EventDispatcher();
    void	dispatchEvent();
    void	pushEvent(Event *event);
    void	pushEvent(Event *event, int ms);
    void	registerEvent(std::string const &type, void (*function)(Event &));
    template <class InstanceClass>
    void	registerEvent(std::string const &type, InstanceClass *instance,
		 	      void (InstanceClass::*method)(Event &))
  {
    _registeredEvents[type].push_back(new Callback(instance, method));
  }


    void	removeEvent(std::string type);

  private:
    void	dispatch();
    void	dispatchTimed();

    std::map<std::string, std::list<Callback*> >	_registeredEvents;
    std::queue<Event*>					_events;
    std::list<timedPair>				_timedEvents;
    Clock						_clock;
};

#endif		/* _EVENTDISPATCHER_ */
