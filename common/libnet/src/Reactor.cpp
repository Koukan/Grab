/*
 * Reactor.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#define NOMINMAX
#include <algorithm>
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_USE_NAMESPACE

class TimeoutHelper : public EventHandler
{
  public:
	TimeoutHelper(std::function <void (size_t)> func, bool repeat) : _func(func), _repeat(repeat)
	{}

	void handleTimeout(size_t delay)
	{
		_func(delay);
		if (!_repeat)
			delete this;
	}

  private:
	std::function <void (size_t)> 	_func;
	bool				_repeat;
};

bool Reactor::timerdata::operator<(timerdata const &other) const
{
	return this->timeout < other.timeout;
}

Reactor::Reactor() : _wait(true), _timerIdgenerator(0)
{}

Reactor::~Reactor()
{}

void	Reactor::stopWaiting()
{
	_wait = false;
}

uint32_t	Reactor::scheduleTimer(EventHandler &handler, size_t delay, bool repeat)
{
	timerdata data;

	data.repeat = repeat;
	data.delay = delay;
	data.handler = &handler;
	data.timeout = static_cast<size_t>(_clock.getElapsedTime()) + delay;
	data.timerId = this->getTimerId();
	_mapHandler[data.timerId] = _listTimeout.insert(data);
	return true;
}

uint32_t	Reactor::scheduleTimer(std::function<void (size_t)> func, size_t delay, bool repeat)
{
	auto handler = new TimeoutHelper(func, repeat);
	return this->scheduleTimer(*handler, delay, repeat);
}

bool		Reactor::cancelTimer(uint32_t timerId)
{
	mapTimeout::iterator it = _mapHandler.find(timerId);
	if (it == _mapHandler.end())
		return false;
	_listTimeout.erase(it->second);
	_mapHandler.erase(it);
	return true;
}

uint32_t Reactor::getTimerId()
{
	return ++_timerIdgenerator;
}

int		Reactor::handleTimers(int &timeout)
{
  auto	time = _clock.getElapsedTime();
  std::multiset<timerdata>::iterator it;
  if (timeout > 0)
  {
	  timeout -= time;
	  if (timeout < 0)
		timeout = 0;
  }
  while (!_listTimeout.empty())
  {
	  it = _listTimeout.begin();
	  auto &tmp = const_cast<timerdata &>(*it);
	  if (tmp.timeout > time)
	  {
		 if (timeout < 0)
			return (tmp.timeout - time);
		 else
			return (std::min(static_cast<int>(tmp.timeout - time), timeout));
	  }
	  tmp.handler->handleTimeout(time - (tmp.timeout - tmp.delay));
	  if (tmp.repeat)
	  {
		  timerdata copy(tmp);
		  copy.timeout = _clock.getElapsedTime() + tmp.delay;
		  _mapHandler[tmp.timerId] = _listTimeout.insert(copy);
	  }
	  _listTimeout.erase(it);
  }
  return timeout;
}
