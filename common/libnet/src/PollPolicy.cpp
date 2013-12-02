/*
 * PollPolicy.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#include <iostream>
#include "PollPolicy.hpp"
#if defined (__unix__)
#	include <poll.h>
#endif

NET_USE_NAMESPACE

PollPolicy::pollpolicydata::pollpolicydata()
{}

PollPolicy::pollpolicydata::pollpolicydata(EventHandler *h, Socket *s, size_t i) : handler(h), socket(s), index(i)
{}

PollPolicy::PollPolicy() : _size(0)
{
	_fds = new struct pollfd[64];
	for	(size_t i = 0; i < 64; ++i)
	{
		_fds[i].events = 0;
		_fds[i].fd = -1;
		_fds[i].revents = 0;
	}
}

PollPolicy::~PollPolicy()
{
	delete[] _fds;
}

bool	PollPolicy::registerHandler(Socket &socket, EventHandler &handler, int mask)
{
  size_t	i;

  if (socket.getHandle() == INVALID_HANDLE)
	 return false;
  HandleMap::iterator it = _handles.find(socket.getHandle());
  if (it != _handles.end())
	 i = it->second.index;
  else if (!_emptySlot.empty())
  {
	 i = _emptySlot.front();
	 _handles[socket.getHandle()] = pollpolicydata(&handler, &socket, i);
	 _emptySlot.pop();
  }
  else
  {
	 _handles[socket.getHandle()] = pollpolicydata(&handler, &socket, _size);
	 i = _size++;
  }
  if (_size > 64)
	  return false;
  _fds[i].fd = socket.getHandle();
  _fds[i].events = 0;
  if ((mask & Reactor::READ )|| (mask & Reactor::ACCEPT))
		 _fds[i].events |= POLLIN;
  if (mask & Reactor::WRITE)
	 _fds[i].events |= POLLOUT;
  return 0;
}

bool	PollPolicy::removeHandler(Socket &socket)
{
  HandleMap::iterator it = _handles.find(socket.getHandle());
  if (it == _handles.end())
	  return false;
  size_t index = it->second.index;
  _fds[index].fd = -1;
  _handles.erase(it);
#if defined(_WIN32)
  size_t first = 0;
  for (size_t second = 0; second < _size; second++)
  {
	  if (_fds[second].fd != -1)
	  {
		 _handles[_fds[second].fd].index = first;
		 _fds[first++] = _fds[second];
	  }
  }
  _size = first;
#else
  _emptySlot.push(index);
#endif
  return true;
}

int		PollPolicy::waitForEvent(int timeout)
{
	int			ret;
	int			i;
	int			nb;

	while (_wait)
	{
		if (_size > 0)
			ret = ::poll(_fds, _size, this->handleTimers(timeout));
		else
		{
			Clock::sleep(this->handleTimers(timeout));
			ret = 0;
		}
		if (ret > 0)
		{
			nb = 0;
			for	(i = 0; nb < ret && i < static_cast<int>(_size); ++i)
			{
				if (_fds[i].revents > 0)
				{
					pollpolicydata &data = _handles[_fds[i].fd];
					if ((_fds[i].revents & POLLHUP) || (_fds[i].revents & POLLERR))
						data.handler->handleClose(*data.socket);
					else
					{
						if ((_fds[i].revents & POLLOUT) && data.handler->handleOutput(*data.socket) <= 0)
						{
							data.handler->handleClose(*data.socket);
							continue ;
						}
						if ((_fds[i].revents & POLLIN) && data.handler->handleInput(*data.socket) <= 0)
							data.handler->handleClose(*data.socket);
					}
					++nb;
				}
			}
		}
		else if (ret == -1 && errno != EINTR)
		  return -1;
		else if (ret == 0 && timeout == 0)
		  return 0;
	}
	return 0;
}
