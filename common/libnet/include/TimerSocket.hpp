#pragma once

#include "EventHandler.hpp"
#include "Socket.hpp"
#include "Clock.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ TimerSocket : public Socket
{
public:
	TimerSocket(Handle handle, EventHandler &handler, size_t delay);
	size_t const			delay;
	EventHandler			&handler;
	Clock					clock;

};

NET_END_NAMESPACE
