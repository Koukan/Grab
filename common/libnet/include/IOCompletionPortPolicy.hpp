#pragma once

#if defined (_WIN32)

#include <map>
#include <queue>
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ IOCompletionPortPolicy : public Reactor
{
public:
	IOCompletionPortPolicy();
	~IOCompletionPortPolicy();

	int		registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	int		removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout) override;

private:
	HANDLE							_iocompletionport;
};

NET_END_NAMESPACE

#endif
