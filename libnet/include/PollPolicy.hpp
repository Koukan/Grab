/*
 * PollPolicy.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef POLLPOLICY_HPP_
#define POLLPOLICY_HPP_

#include <map>
#include <queue>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ PollPolicy : public Reactor
{
public:

	PollPolicy();
	~PollPolicy();

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);

private:
	struct	pollpolicydata
	{
		pollpolicydata();
		pollpolicydata(NetHandler *h, Socket *s, size_t i);
		NetHandler	*handler;
		Socket		*socket;
		size_t		index;
	};

	typedef std::map<Handle, pollpolicydata> HandleMap;


	size_t						_size;
	::pollfd					*_fds;

	HandleMap					_handles;
	std::queue<size_t>			_emptySlot;
};

NET_END_NAMESPACE

#endif /* POLLPOLICY_HPP_ */
