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

PollPolicy::pollpolicydata::pollpolicydata(NetHandler *h, Socket *s, size_t i) : handler(h), socket(s), index(i)
{}

PollPolicy::PollPolicy() : _size(0)
{
	_fds = new struct pollfd[64];
	for	(size_t i = 0; i < 64; ++i)
	{
		_fds[i].events = 0;
		_fds[i].fd = INVALID_HANDLE;
		_fds[i].revents = 0;
	}
}

PollPolicy::~PollPolicy()
{
	delete[] _fds;
}

int	PollPolicy::registerHandler(Socket &socket, NetHandler &handler, int mask)
{
  size_t	i;

  if (socket.getHandle() == INVALID_SOCKET)
	 return -1;
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
	  return -1;
  _fds[i].fd = socket.getHandle();
  _fds[i].events = 0;
  if ((mask & Reactor::READ )|| (mask & Reactor::ACCEPT))
		 _fds[i].events |= POLLIN;
  if (mask & Reactor::WRITE)
	 _fds[i].events |= POLLOUT;
  return 0;
}

int	PollPolicy::removeHandler(Socket &socket)
{
  HandleMap::iterator it = _handles.find(socket.getHandle());
  if (it == _handles.end())
	  return -1;
  _fds[it->second.index].fd = INVALID_HANDLE;
   _emptySlot.push(it->second.index);
  _handles.erase(it);
  return 0;
}

int		PollPolicy::waitForEvent(int timeout)
{
	int			ret;
	int			i;
	int			nb;
	NetHandler	*handler;
	Socket		*socket;

	while (_wait)
	{
		ret = ::poll(_fds, _size, this->handleTimers(timeout));
		if (ret > 0)
		{
			nb = 0;
			for	(i = 0; nb < ret && i < static_cast<int>(_size); ++i)
			{
				if (_fds[i].revents > 0)
				{
					handler = _handles[_fds[i].fd].handler;
					socket = _handles[_fds[i].fd].socket;
					if (_fds[i].revents & POLLHUP)
						handler->handleClose(*socket);
					else
					{
						if (_fds[i].revents & POLLOUT)
							handler->handleOutput(*socket);
						if ((_fds[i].revents & POLLIN) && handler->handleInput(*socket) <= 0)
							handler->handleClose(*socket);
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
