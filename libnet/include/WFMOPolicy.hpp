#pragma once

#if defined (_WIN32)

#include <map>
#include <queue>
#include "Reactor.hpp"
#include "NetHandler.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ WFMOPolicy : public Reactor
{
public:
	WFMOPolicy(void);
	~WFMOPolicy(void);

	int		registerHandler(Socket &socket, NetHandler &handler, int mask);
	int		removeHandler(Socket &socket);
	int		waitForEvent(int timeout);

private:
	typedef std::map<Handle, size_t> SocketMap;
	struct wfmopolicydata
	{
		NetHandler	*handler;
		Socket		*socket;
	};

	void	dispatchEvent(DWORD index, LPWSANETWORKEVENTS netEvent);

	DWORD							_size;
	HANDLE							_handles[MAXIMUM_WAIT_OBJECTS];
	wfmopolicydata					_data[MAXIMUM_WAIT_OBJECTS];
	SocketMap						_map;
	std::queue<size_t>				_emptySlot;
};

NET_END_NAMESPACE

#endif
