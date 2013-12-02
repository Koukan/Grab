#pragma once

#include <unordered_map>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "EventHandler.hpp"
#include "Clock.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Reactor based on kqueue()
 \details Available on Mac OS, FreeBSD and other BSD
 */
class NET_DLLREQ KqueuePolicy : public Reactor, public Socket
{
public:
	KqueuePolicy();
	~KqueuePolicy();

	bool	registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	bool	removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout = -1) override;

	uint32_t	scheduleTimer(EventHandler &handler, size_t delay, bool repeat = false) override;
	bool		cancelTimer(uint32_t timerId) override;

private:
	struct	timerdata
	{
		EventHandler	*handler;
		size_t		delay;
		size_t		timerid;
		Clock		clock;
	};

	std::unordered_map<uint32_t, timerdata*>   	_timers;
};

NET_END_NAMESPACE
