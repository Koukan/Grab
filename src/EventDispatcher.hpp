#ifndef		_EVENTDISPATCHER_
#define 	_EVENTDISPATCHER_

#include <map>
#include <list>
#include <queue>
#include <string>
#include "Event.hpp"
#include "Clock.hpp"
#include "Callback.hpp"
#include "TimeEffectManager.hpp"

typedef std::pair<unsigned int, Event*>				timedPair;
typedef std::map<std::string, std::list<Callback*> >		eventMap;
typedef std::map<TimeEffectGroup*, std::list<timedPair> >	timedEventMap;

class EventDispatcher
{
  public:
    EventDispatcher();
    virtual ~EventDispatcher();
    void	dispatchEvent();
    void	pushEvent(Event *event);
    void	pushEvent(Event *event, int ms,
		    	std::string const &timeEffectGroup = "default");
    void	registerEvent(std::string const &type, void (*function)(Event &));
    template <class InstanceClass>
    void	registerEvent(std::string const &type, InstanceClass &instance,
		 	      void (InstanceClass::*method)(Event &));
    void	removeEvent(std::string const &type);

  private:
    void	dispatch();
    void	dispatchTimed(std::list<timedPair> &list, unsigned int time);

    eventMap		_registeredEvents;
    std::queue<Event*>	_events;
    timedEventMap	_timedEvents;
};

#include "EventDispatcher.ipp"

#endif		/* _EVENTDISPATCHER_ */
