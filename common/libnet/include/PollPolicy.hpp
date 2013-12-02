/*
 * PollPolicy.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef POLLPOLICY_HPP_
#define POLLPOLICY_HPP_

#include <unordered_map>
#include <queue>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Reactor based on poll()
 \details Available on all OSes but not very efficient nor stable
 */
class NET_DLLREQ PollPolicy : public Reactor
{
public:

	PollPolicy();
	~PollPolicy();

	bool	registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	bool	removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout = -1) override;

private:
	struct	pollpolicydata
	{
		pollpolicydata();
		pollpolicydata(EventHandler *h, Socket *s, size_t i);
		EventHandler	*handler;
		Socket		*socket;
		size_t		index;
	};

	typedef std::unordered_map<Handle, pollpolicydata> HandleMap;


	size_t						_size;
	::pollfd					*_fds;

	HandleMap					_handles;
	std::queue<size_t>			_emptySlot;
};

NET_END_NAMESPACE

#endif /* POLLPOLICY_HPP_ */
