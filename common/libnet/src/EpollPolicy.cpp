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
  _epollfd = epoll_create(1);
}

EpollPolicy::~EpollPolicy()
{
  ::close(_epollfd);
}

int		EpollPolicy::registerHandler(Socket &socket, NetHandler &handler, int mask)
{
  struct epoll_event ev;

  int	mode = (socket.getNetHandler()) ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
  socket.setNetHandler(&handler);
  ev.data.u64 = 0;
  ev.data.ptr = &socket;
  ev.events = 0;
  if (mask & Reactor::READ || mask & Reactor::ACCEPT)
	  ev.events |= EPOLLIN;
  if (mask & Reactor::WRITE)
	  ev.events |= EPOLLOUT;
  return ::epoll_ctl(_epollfd, mode, socket.getHandle(), &ev);
}

int		EpollPolicy::removeHandler(Socket &socket)
{
  socket.setNetHandler(0);
  return ::epoll_ctl(_epollfd, EPOLL_CTL_DEL, socket.getHandle(), 0);
}

int		EpollPolicy::waitForEvent(int timeout)
{
  int			ret, i;
  Socket		*socket;
  NetHandler	*handler;
  struct epoll_event	ev[50];

  while	(_wait)
  {
	ret = ::epoll_wait(_epollfd, ev, 50, timeout);
	if (ret == -1 && errno != EINTR)
		return -1;
	else if (ret == 0 && timeout == 0)
	  return 0;
	for	(i = 0; i < ret; ++i)
	{
		socket = static_cast<Socket *>(ev[i].data.ptr);
		handler = socket->getNetHandler();
		if (ev[i].events & EPOLLHUP)
			handler->handleClose(*socket);
		else
		{
			if (ev[i].events & EPOLLOUT && handler->handleOutput(*socket) <= 0)
			{
				handler->handleClose(*socket);
				continue ;
			}
			if ((ev[i].events & EPOLLIN) && handler->handleInput(*socket) <= 0)
				handler->handleClose(*socket);
		}
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
		static_cast<TimerSocket&>(socket).getTimeoutHandler().handleTimeout();
	}
	return ret;
}

int     EpollPolicy::scheduleTimer(NetHandler &handler, size_t delay, bool repeat)
{	
	int	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
   	if (timerfd < 0)
		return -1;
	struct itimerspec	timerspec;
	timerspec.it_value.tv_sec = delay / 1000;
	timerspec.it_value.tv_nsec = (delay % 1000) * 1000;
	if (repeat)
		timerspec.it_interval = timerspec.it_value;
	if (timerfd_settime(timerfd, 0, &timerspec, 0) == -1)
		return -1;
	TimerSocket	*tmp = new TimerSocket(timerfd, handler);
	this->registerHandler(*tmp, *this, Reactor::READ);
	_timers[&handler] = tmp;
	return 0;
}

int     EpollPolicy::cancelTimer(NetHandler &handler)
{	
	std::map<NetHandler*, Socket*>::iterator it = _timers.find(&handler);
  	if (it != _timers.end())
  	{
		this->removeHandler(*it->second);
		delete it->second;
	  	_timers.erase(it);
	  	return 0;
  	}
  	return -1;
}

#endif
