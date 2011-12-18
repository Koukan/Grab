/*
 * EpollPolicy.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#if defined (__linux__)
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>
#include "network.h"
#include "EpollPolicy.hpp"

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
  int	ret;

  epollpolicydata	*data = &_handlers[socket.getHandle()];
  data->handler = &handler;
  data->socket = &socket;
  ev.data.ptr = data;
  ev.events = 0;
  if (mask & Reactor::READ || mask & Reactor::ACCEPT)
	  ev.events |= EPOLLIN;
  if (mask & Reactor::WRITE)
	  ev.events |= EPOLLOUT;
  ret = ::epoll_ctl(_epollfd, EPOLL_CTL_MOD, socket.getHandle(), &ev);
   if (ret == 0)
     return 0;
   if (ret == -1 && errno != ENOENT)
     return -1;
  return ::epoll_ctl(_epollfd, EPOLL_CTL_ADD, socket.getHandle(), &ev);
}

int		EpollPolicy::removeHandler(Socket &socket)
{
  _handlers.erase(socket.getHandle());
  return ::epoll_ctl(_epollfd, EPOLL_CTL_DEL, socket.getHandle(), 0);
}

int		EpollPolicy::waitForEvent(int timeout)
{
  int			ret, i;
  epollpolicydata	*data;
  struct epoll_event	ev[50];

  while	(_wait)
  {
	ret = ::epoll_wait(_epollfd, ev, 50, this->handleTimers(timeout));
	if (ret == -1 && errno != EINTR)
		return -1;
	else if (ret == 0 && timeout == 0)
	  return 0;
	for	(i = 0; i < ret; ++i)
	{
		data = static_cast<epollpolicydata *>(ev[i].data.ptr);
		if (ev[i].events & EPOLLHUP)
			data->handler->handleClose(*(data->socket));
		else
		{
			if (ev[i].events & EPOLLOUT)
				data->handler->handleOutput(*(data->socket));
			if ((ev[i].events & EPOLLIN) && data->handler->handleInput(*(data->socket)) <= 0)
				data->handler->handleClose(*(data->socket));
		}
	}
  }
  return 0;
}

#endif
