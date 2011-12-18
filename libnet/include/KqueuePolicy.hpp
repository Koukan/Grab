/*
 * KqueuePolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef KQUEUEPOLICY_HPP_
#define KQUEUEPOLICY_HPP_

#if defined (__FreeBSD__)
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

private:
	struct	kqueuepolicydata
	{
		NetHandler	*handler;
		Socket		*socket;
	};

	int		_kqueuefd;
	std::map<Handle, kqueuepolicydata>	_handlers;
};

NET_END_NAMESPACE

#endif

#endif /* KQUEUEPOLICY_HPP_ */
