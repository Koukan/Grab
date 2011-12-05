/*
 * EpollPolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef EPOLLPOLICY_HPP_
#define EPOLLPOLICY_HPP_

#include <map>
#include "network.h"
#include "Reactor.hpp"
#include "NetHandler.hpp"

class EpollPolicy : public Reactor
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

#endif /* EPOLLPOLICY_HPP_ */
