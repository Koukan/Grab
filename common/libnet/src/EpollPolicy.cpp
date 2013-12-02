/*
 * EpollPolicy.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#if defined (HAVE_EPOLL)
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <errno.h>
#include <unistd.h>
#include "network.h"
#include "EpollPolicy.hpp"
#include "TimerSocket.hpp"

#include <iostream>
NET_USE_NAMESPACE

EpollPolicy::EpollPolicy()
{
  _handle = epoll_create(1);
}

EpollPolicy::~EpollPolicy()
{
}

bool		EpollPolicy::registerHandler(Socket &socket, EventHandler &handler, int mask)
{
  struct epoll_event ev;

  int	mode = (socket.getEventHandler()) ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
  socket.setEventHandler(&handler);
  ev.data.u64 = 0;
  ev.data.ptr = &socket;
  ev.events = 0;
  if (mask & Reactor::READ || mask & Reactor::ACCEPT)
	  ev.events |= EPOLLIN;
  if (mask & Reactor::WRITE)
	  ev.events |= EPOLLOUT;
  return (::epoll_ctl(_handle, mode, socket.getHandle(), &ev) != -1);
}

bool		EpollPolicy::removeHandler(Socket &socket)
{
  socket.setEventHandler(nullptr);
  return (::epoll_ctl(_handle, EPOLL_CTL_DEL, socket.getHandle(), 0) != -1);
}

int		EpollPolicy::waitForEvent(int timeout)
{
  int			ret, i;
  Socket		*socket;
  EventHandler	*handler;
  struct epoll_event	ev[50];
  Clock			clock;

  while	(_wait)
  {
	ret = ::epoll_wait(_handle, ev, 50, timeout);
	if (ret == -1 && errno != EINTR)
		return -1;
	else if (ret == 0 && timeout == 0)
	  return 0;
	if (timeout > 0)
	{
		timeout -= clock.getElapsedTime();
		clock.update();
		if (timeout < 0)
			timeout = 0;
	}
	for	(i = 0; i < ret; ++i)
	{
		socket = static_cast<Socket *>(ev[i].data.ptr);
		handler = socket->getEventHandler();
		if (ev[i].events & EPOLLHUP)
			handler->handleClose(*socket);
		else if (ev[i].events & EPOLLOUT && handler->handleOutput(*socket) <= 0)
			handler->handleClose(*socket);
		else if ((ev[i].events & EPOLLIN) && handler->handleInput(*socket) <= 0)
			handler->handleClose(*socket);
	}
  }
  return 0;
}

int		EpollPolicy::handleInput(Socket &socket)
{
	uint64_t	cnt;
	int ret = read(socket.getHandle(), &cnt, sizeof(cnt));
	if (ret > 0)
	{
		TimerSocket	&timersocket = static_cast<TimerSocket&>(socket);
		auto delay = timersocket.clock.getElapsedTime();
		timersocket.clock.update();
		timersocket.handler.handleTimeout(delay);
	}
	return ret;
}

uint32_t	EpollPolicy::scheduleTimer(EventHandler &handler, size_t delay, bool repeat)
{	
	int	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
   	if (timerfd < 0)
		return 0;
	struct itimerspec	timerspec;
	timerspec.it_value.tv_sec = delay / 1000;
	timerspec.it_value.tv_nsec = (delay % 1000) * 1000000;
	if (repeat)
		timerspec.it_interval = timerspec.it_value;
	else
	{
		timerspec.it_interval.tv_sec = 0;
		timerspec.it_interval.tv_nsec = 0;
	}
	if (timerfd_settime(timerfd, 0, &timerspec, 0) == -1)
		return 0;
	TimerSocket	*tmp = new TimerSocket(timerfd, handler, delay);
	if (!this->registerHandler(*tmp, *this, Reactor::READ))
		return 0;
	auto id = this->getTimerId();
	_timers[id] = tmp;
	return id;
}

bool     EpollPolicy::cancelTimer(uint32_t timerId)
{	
	auto it = _timers.find(timerId);
  	if (it == _timers.end())
		return false;
	this->removeHandler(*it->second);
	delete it->second;
	_timers.erase(it);
	return false;
}

#endif
