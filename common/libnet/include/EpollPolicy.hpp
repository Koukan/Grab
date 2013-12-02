/*
 * EpollPolicy.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#pragma once

#include <unordered_map>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Reactor base on epoll()
 \details Only available on linux but performant and robust
 */
class NET_DLLREQ EpollPolicy : public Reactor, public EventHandler, public Socket
{
public:
	EpollPolicy();
	~EpollPolicy();

	bool	registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	bool	removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout = -1) override;
	
	int		handleInput(Socket &socket) override;
	uint32_t	scheduleTimer(EventHandler &handler, size_t delay, bool repeat = false) override;
	bool		cancelTimer(uint32_t timerId) override;

private:
	std::unordered_map<uint32_t, Socket*>   	_timers;
};

NET_END_NAMESPACE
