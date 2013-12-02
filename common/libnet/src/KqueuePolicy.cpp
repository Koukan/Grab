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
  _handle = kqueue();
}

KqueuePolicy::~KqueuePolicy()
{
}

bool		KqueuePolicy::registerHandler(Socket &socket, EventHandler &handler, int mask)
{
  struct kevent ev[2];
  int			pos = 0;

  socket.setEventHandler(&handler);
  EV_SET(&ev[0], socket.getHandle(), EVFILT_READ, EV_DISABLE, 0, 0, 0);
  EV_SET(&ev[1], socket.getHandle(), EVFILT_WRITE, EV_DISABLE, 0, 0, 0);
  ::kevent(_handle, ev, 2, 0, 0, 0);
  if (mask & Reactor::READ || mask & Reactor::ACCEPT)
  	EV_SET(&ev[pos++], socket.getHandle(), EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, &socket);
  if (mask & Reactor::WRITE)
  	EV_SET(&ev[pos++], socket.getHandle(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, &socket);
  if (pos == 1 && mask & Reactor::WRITE)
		::kevent(_handle, &ev[1], pos, 0, 0, 0);
 	else
  		::kevent(_handle, ev, pos, 0, 0, 0);
	return true;
}

bool		KqueuePolicy::removeHandler(Socket &socket)
{
  socket.setEventHandler(nullptr);
  struct kevent ev;
  EV_SET(&ev, socket.getHandle(), 0, EV_DELETE, 0, 0, 0);
  return (::kevent(_handle, &ev, 1, 0, 0, 0) == 0);
}

int		KqueuePolicy::waitForEvent(int timeout)
{
  	int						ret, i, time;
	Socket					*socket;
	EventHandler			*handler;
  	struct kevent			ev[50];
  	struct timespec 		timespec;
	Clock					clock;

	while (_wait)
	{
		time = timeout;
		if (time >= 0)
		{
			timespec.tv_sec = time / 1000;
			timespec.tv_nsec = (time % 1000) * 1000000;
		}
		ret = ::kevent(_handle, 0, 0, ev, 50, (time < 0) ? 0 : &timespec);
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
			if (ev[i].filter == EVFILT_TIMER)
			{
				timerdata *timer = reinterpret_cast<timerdata*>(ev[i].udata);
				auto delay = timer->clock.getElaspedTime();
				timer->clock.update();
				timer->handler->handleTimeout(delay);
				continue ;
			}
			socket = static_cast<Socket *>(ev[i].udata);
			handler = socket->getEventHandler();
			if (ev[i].filter == EVFILT_WRITE && handler->handleOutput(*socket) <= 0)
				handler->handleClose(*socket);
			else if (ev[i].filter == EVFILT_READ && handler->handleInput(*socket) <= 0)
				handler->handleClose(*socket);
		}
  }
  return 0;
}

uint32_t	KqueuePolicy::scheduleTimer(EventHandler &handler, size_t delay, bool repeat)
{
	struct kevent ev;
	
	auto timer = new timerdata();
	timer->handler = &handler;
	timer->delay = delay;
	timer->timerid = this->getTimerId();
	if (repeat)
		EV_SET(&ev, timer->timerid, EVFILT_TIMER, EV_ADD | EV_ENABLE, 0, delay, timer);
	else
		EV_SET(&ev, timer->timerid, EVFILT_TIMER, EV_ADD | EV_ENABLE | EV_ONESHOT, 0, delay, timer);
	if (::kevent(_handle, &ev, 1, 0, 0, 0) == -1)
	{
		delete timer;
		return 0;
	}
	_timers[timer->timerid] = timer;
	return timer->timerid;
}

bool		KqueuePolicy::cancelTimer(uint32_t timerId)
{
	auto it = _timers.find(timerId);

	if (it == _timers.end())
		return false;
	struct kevent ev;
	EV_SET(&ev, timerId, EVFILT_TIMER, EV_DELETE, 0, 0, 0);
	if (::kevent(_handle, &ev, 1, 0, 0, 0) == -1)
		return false;
	delete it->second;
	_timers.erase(it);
	return true;
}

#endif
