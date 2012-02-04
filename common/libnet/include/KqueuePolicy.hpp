/*
 * KqueuePolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef KQUEUEPOLICY_HPP_
#define KQUEUEPOLICY_HPP_

#include <map>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ KqueuePolicy : public Reactor
{
public:
	KqueuePolicy();
	~KqueuePolicy();

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);

	int		scheduleTimer(NetHandler &handler, size_t delay, bool repeat = false);
	int		cancelTimer(NetHandler &handler);

private:
	int		_kqueuefd;
	size_t	_timerid;
	std::map<NetHandler*, size_t>   	_timers;
};

NET_END_NAMESPACE

#endif /* KQUEUEPOLICY_HPP_ */
