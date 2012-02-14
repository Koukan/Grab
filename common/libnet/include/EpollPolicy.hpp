/*
 * EpollPolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef EPOLLPOLICY_HPP_
#define EPOLLPOLICY_HPP_

#include <map>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ EpollPolicy : public Reactor, public NetHandler, public Socket
{
public:
	EpollPolicy();
	~EpollPolicy();

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);
	
	int		handleInput(Socket &socket);
	int		scheduleTimer(NetHandler &handler, size_t delay, bool repeat = false);
	int		cancelTimer(NetHandler &handler);

private:
	std::map<NetHandler*, Socket*>   	_timers;
};

NET_END_NAMESPACE

#endif /* EPOLLPOLICY_HPP_ */
