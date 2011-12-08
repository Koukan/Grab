/*
 * Reactor.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#define NOMINMAX
#include <algorithm>
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_USE_NAMESPACE

bool Reactor::schedulingdata::operator<(schedulingdata const &other) const
{
	return this->timeout < other.timeout;
}

Reactor::Reactor() : _wait(true)
{}

Reactor::~Reactor()
{}

void	Reactor::stopWaiting()
{
	_wait = false;
}

int		Reactor::scheduleTimer(NetHandler &handler, size_t delay, bool repeat)
{
  schedulingdata data;

  data.delay = delay;
  data.repeat = repeat;
  data.handler = &handler;
  data.timeout = static_cast<size_t>(_clock.getElapsedTime()) + delay;
  _mapHandler[&handler] = (_listTimeout.insert(data)).first;
  return 0;
}

int		Reactor::cancelTimer(NetHandler &handler)
{
  mapTimeout::iterator it = _mapHandler.find(&handler);
  if (it != _mapHandler.end())
  {
	  _listTimeout.erase(it->second);
	  _mapHandler.erase(it);
	  return 0;
  }
  return -1;
}

int		Reactor::handleTimers(int &timeout)
{
  size_t	time = static_cast<size_t>(_clock.getElapsedTime());
  std::set<schedulingdata>::iterator it;
  if (timeout > 0)
  {
	  timeout -= time;
	  if (timeout < 0)
		timeout = 0;
  }
  while (!_listTimeout.empty())
  {
	  it = _listTimeout.begin();
	  schedulingdata const &tmp = *it;
	  if (tmp.timeout > time)
	  {
		 if (timeout < 0)
			return (tmp.timeout - time);
		 else
			return (std::min(static_cast<int>(tmp.timeout - time), timeout));
	  }
	  tmp.handler->handleTimeout();
	  if (tmp.repeat)
	  {
		  schedulingdata copy = tmp;
		  copy.timeout += tmp.delay;
		  _mapHandler[tmp.handler] = (_listTimeout.insert(copy)).first;
	  }
	  _listTimeout.erase(it);
  }
  return timeout;
}
