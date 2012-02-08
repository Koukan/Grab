/*
 * KqueuePolicy.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#if defined (HAVE_KQUEUE)
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include "network.h"
#include "KqueuePolicy.hpp"

NET_USE_NAMESPACE

KqueuePolicy::KqueuePolicy()
{
  _kqueuefd = kqueue();
  _timerid = 0;
}

KqueuePolicy::~KqueuePolicy()
{
  ::close(_kqueuefd);
}

int		KqueuePolicy::registerHandler(Socket &socket, NetHandler &handler, int mask)
{
  struct kevent ev[2];
  int			pos = 0;

  socket.setNetHandler(&handler);
  if (mask & Reactor::READ || mask & Reactor::ACCEPT)
  	EV_SET(&ev[pos++], socket.getHandle(), EVFILT_READ, EV_ADD, 0, 0, &socket);
  if (mask & Reactor::WRITE)
  	EV_SET(&ev[pos++], socket.getHandle(), EVFILT_WRITE, EV_ADD, 0, 0, &socket);
  if (pos == 1 && mask & Reactor::WRITE)
		return ::kevent(_kqueuefd, &ev[1], pos, 0, 0, 0);
 	else
  		return ::kevent(_kqueuefd, ev, pos, 0, 0, 0);
}

int		KqueuePolicy::removeHandler(Socket &socket)
{
  socket.setNetHandler(0);
  struct kevent ev;
  EV_SET(&ev, socket.getHandle(), 0, EV_DELETE, 0, 0, 0);
  return ::kevent(_kqueuefd, &ev, 1, 0, 0, 0);
}

int		KqueuePolicy::waitForEvent(int timeout)
{
  	int						ret, i, time;
	Socket					*socket;
	NetHandler				*handler;
  	struct kevent			ev[50];
  	struct timespec 		timespec;

  while	(_wait)
  {
	time = timeout;
  	if (time >= 0)
	{
	  timespec.tv_sec = time / 1000;
	  timespec.tv_nsec = (time % 1000) * 1000000;
	}		
	ret = ::kevent(_kqueuefd, 0, 0, ev, 50, (time < 0) ? 0 : &timespec);
	if (ret == -1 && errno != EINTR)
		return -1;
	else if (ret == 0 && timeout == 0)
	  return 0;
	for	(i = 0; i < ret; ++i)
	{
		if (ev[i].filter == EVFILT_TIMER)
		{
			reinterpret_cast<NetHandler*>(ev[i].udata)->handleTimeout();
			continue ;
		}
		socket = static_cast<Socket *>(ev[i].udata);
		handler = socket->getNetHandler();
		if ((ev[i].filter == EVFILT_WRITE) && handler->handleOutput(*socket) <= 0)
		{
			handler->handleClose(*socket);
			continue ;
		}
		else if (ev[i].filter == EVFILT_READ && handler->handleInput(*socket) <= 0)
			handler->handleClose(*socket);
	}
  }
  return 0;
}

int		KqueuePolicy::scheduleTimer(NetHandler &handler, size_t delay, bool repeat)
{
	struct kevent ev;
	
	if (repeat)
		EV_SET(&ev, _timerid, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, delay, &handler);
	else
		EV_SET(&ev, _timerid, EVFILT_TIMER, EV_ADD | EV_ENABLE | EV_ONESHOT, 0, delay, &handler);
	_timers[&handler] = _timerid++;
	return ::kevent(_kqueuefd, &ev, 1, 0, 0, 0);
}

int		KqueuePolicy::cancelTimer(NetHandler &handler)
{
	std::map<NetHandler*, size_t>::iterator it = _timers.find(&handler);

	if (it != _timers.end())
	{
		struct kevent ev;
		EV_SET(&ev, it->second, EVFILT_TIMER, EV_DELETE, 0, 0, 0);
		return ::kevent(_kqueuefd, &ev, 1, 0, 0, 0);
	}
	return -1;
}

#endif
