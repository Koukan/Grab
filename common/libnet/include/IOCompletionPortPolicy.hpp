#pragma once

#if defined (_WIN32)

#include <map>
#include <queue>
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ IOCompletionPortPolicy : public Reactor
{
public:
	IOCompletionPortPolicy();
	~IOCompletionPortPolicy();

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);

private:
	HANDLE							_iocompletionport;
};

NET_END_NAMESPACE

#endif
