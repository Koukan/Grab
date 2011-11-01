#ifndef		_EVENTDISPATCHER_
#define 	_EVENTDISPATCHER_

#include <map>
#include <list>
#include <queue>
#include <string>
#include "Event.hpp"
#include "Clock.hpp"
#include "Callback.hpp"

typedef std::pair<unsigned int, Event*>			timedPair;
typedef std::map<std::string, std::list<Callback*> >	eventMap;

class EventDispatcher
{
  public:
    EventDispatcher();
    virtual ~EventDispatcher();
    void	dispatchEvent(double elapsedTime);
    void	pushEvent(Event *event);
    void	pushEvent(Event *event, int ms);
    void	registerEvent(std::string const &type, void (*function)(Event &));
    template <class InstanceClass>
    void	registerEvent(std::string const &type, InstanceClass &instance,
		 	      void (InstanceClass::*method)(Event &));
    void	removeEvent(std::string const &type);

  private:
    void	dispatch();
    void	dispatchTimed(std::list<timedPair> &list, unsigned int time);

    eventMap			_registeredEvents;
    std::queue<Event*>		_events;
    std::list<timedPair>	_timedEvents;
    std::list<timedPair>	_timedRelativeEvents;
    unsigned int		_time;
    unsigned int		_relativeTime;
};

#include "EventDispatcher.ipp"

#endif		/* _EVENTDISPATCHER_ */
