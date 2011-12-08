/*
 * EpollPolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef EPOLLPOLICY_HPP_
#define EPOLLPOLICY_HPP_

#if defined (__linux__)
#include <map>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ EpollPolicy : public Reactor
{
public:
	EpollPolicy();
	~EpollPolicy();

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);

private:
	struct	epollpolicydata
	{
		NetHandler	*handler;
		Socket		*socket;
	};

	int		_epollfd;
	std::map<Handle, epollpolicydata>	_handlers;
};

NET_END_NAMESPACE

#endif

#endif /* EPOLLPOLICY_HPP_ */
