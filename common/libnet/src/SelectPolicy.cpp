#include "SelectPolicy.hpp"

NET_USE_NAMESPACE

#include <iostream>
SelectPolicy::SelectPolicy() : _maxfd(0), _rsize(0), _wsize(0), _esize(0)
{
	FD_ZERO(&_read_set);
	FD_ZERO(&_write_set);
	FD_ZERO(&_except_set);
}

SelectPolicy::~SelectPolicy()
{}

bool	SelectPolicy::registerHandler(Socket &socket, EventHandler &handler, int mask)
{
	auto handle = socket.getHandle();
	auto it = _sockets.find(&socket);
	if (it != _sockets.end())
	{
		int old_mask = it->second;
		if (old_mask == mask)
			return true;
		if (old_mask & Reactor::READ || old_mask & Reactor::ACCEPT)
			_rsize--;
		if (old_mask & Reactor::WRITE)
			_wsize--;
		_esize--;
	}
	if (mask & Reactor::READ || mask & Reactor::ACCEPT)
	{
		FD_SET(handle, &_read_set);
		_rsize++;
	}
	if (mask & Reactor::WRITE)
	{
		FD_SET(handle, &_write_set);
		_wsize++;
	}
	FD_SET(handle, &_except_set);
	_esize++;
	if (handle > _maxfd)
		_maxfd = (size_t)handle;
	_sockets[&socket] = mask;
	socket.setEventHandler(&handler);
	return true;
}

bool	SelectPolicy::removeHandler(Socket &socket)
{
	auto handle = socket.getHandle();
	auto it = _sockets.find(&socket);
	if (it == _sockets.end())
		return false;
	int mask = it->second;
	if (mask & Reactor::READ || mask & Reactor::ACCEPT)
	{
		FD_CLR(handle, &_read_set);
		_rsize--;
	}
	if (mask & Reactor::WRITE)
	{
		FD_CLR(handle, &_write_set);
		_wsize--;
	}
	FD_CLR(handle, &_except_set);
	_esize--;
	_sockets.erase(it);
	socket.setEventHandler(nullptr);
#ifndef _WIN32
	if (handle == _maxfd)
	{
		int max = 0;
		for (auto &it : _sockets)
			if (it.first->getHandle() > max)
				max = it.first->getHandle();
		_maxfd = max;
	}
#endif
	return true;
}

int		SelectPolicy::waitForEvent(int timeout)
{
	struct timeval time;
	int ret;
	fd_set *set[3];
	Clock	clock;

	while (_wait)
	{
		int t = this->handleTimers(timeout);
		if (t >= 0)
		{
			time.tv_sec = t / 1000;
			time.tv_usec = (t % 1000) * 1000;
		}
		fd_set rs = _read_set, ws = _write_set, es = _except_set;
		set[0] = (_rsize == 0) ? nullptr : &rs;
		set[1] = (_wsize == 0) ? nullptr : &ws;
		set[2] = (_esize == 0) ? nullptr : &es;
#if defined (_WIN32)
		if (!set[0] && !set[1] && !set[2])
		{
			Net::Clock::sleep(t);
			continue ;
		}
		else
#endif
			ret = ::select(_maxfd + 1, set[0], set[1], set[2], (t < 0) ? nullptr : &time);
		if ((ret == -1 && errno == EINTR) || (ret == 0 && timeout != 0))
			continue ;
		if (ret == -1)
			std::cerr << Net::getLastError() << std::endl;
		if (ret == -1  || (ret == 0 && timeout == 0))
			return ret;
		if (timeout > 0)
		{
			timeout -= clock.getElapsedTime();
			clock.update();
			if (timeout < 0)
				timeout = 0;
		}
		for (auto it = _sockets.begin(); it != _sockets.end();)
		{
			auto socket = it->first;
			auto handler = socket->getEventHandler();
			auto handle = socket->getHandle();
			++it;
			if (FD_ISSET(handle, &es))
				handler->handleClose(*socket);
			else
			{
				if (FD_ISSET(handle, &rs) && handler->handleInput(*socket) <= 0)
						handler->handleClose(*socket);
				else if (FD_ISSET(handle, &ws) && handler->handleOutput(*socket) <= 0)
						handler->handleClose(*socket);
			}
		}
	}
	return 0;
}
