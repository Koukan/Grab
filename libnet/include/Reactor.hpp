/*
 * Reactor.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef REACTOR_HPP_
#define REACTOR_HPP_

#include <set>
#include <map>
#include "network.h"
#include "Socket.hpp"
#include "Clock.hpp"

class NetHandler;

class Reactor
{
public:
	Reactor();
	virtual ~Reactor();

	enum	EventMask
	{
		READ = 1,
		WRITE = 2,
		ACCEPT = 4
	};

	virtual int		registerHandler(Socket &socket, NetHandler &handler, int mask) = 0;
	virtual int		removeHandler(Socket &socket) = 0;
	virtual int		waitForEvent(int timeout = -1) = 0;
	virtual	int		scheduleTimer(NetHandler &handler, size_t delay, bool repeat = false);
	virtual	int		cancelTimer(NetHandler &handler);
	virtual void	stopWaiting();

protected:
	struct	schedulingdata
	{
		bool operator<(schedulingdata const &other) const;

		size_t		timeout;
		NetHandler	*handler;
		size_t		delay;
		bool		repeat;
	};
	typedef std::map<NetHandler*, std::set<schedulingdata>::iterator> mapTimeout;

	int				handleTimers(int &timeout);

	bool			_wait;
	Clock			_clock;
	std::set<schedulingdata>	_listTimeout;
	mapTimeout		_mapHandler;
};

#endif /* REACTOR_HPP_ */
