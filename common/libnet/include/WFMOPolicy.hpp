#pragma once

#if defined (_WIN32)

#include <unordered_map>
#include <queue>
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Reactor based on WaitForMultipleObjects
 \details Only available on Windows but efficient, however is limited to 64 handles
 */
class NET_DLLREQ WFMOPolicy : public Reactor
{
public:
	WFMOPolicy();
	~WFMOPolicy();

	bool	registerHandler(HANDLE handle, EventHandler &handler);
	bool	registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	bool	removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout) override;
	uint32_t	scheduleTimer(EventHandler &handler, size_t delay, bool repeat = false) override;
	bool		cancelTimer(uint32_t timerId) override;

private:
	typedef std::unordered_map<HANDLE, size_t> SocketMap;
	struct wfmopolicydata
	{
		EventHandler	*handler;
		Socket		*socket;
		bool		isSocket;
	};
	struct timerdata
	{
		EventHandler		*handler;
		LARGE_INTEGER	lastTick;
	};

	static void	CALLBACK TimerAPCProc(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue);
	void	dispatchEvent(DWORD index, LPWSANETWORKEVENTS netEvent);
	int		attributeIndex(HANDLE handle);

	DWORD							_size;
	HANDLE							_handles[MAXIMUM_WAIT_OBJECTS];
	wfmopolicydata					_data[MAXIMUM_WAIT_OBJECTS];
	SocketMap						_map;
	std::unordered_map<uint32_t, std::pair<HANDLE, timerdata *> >   _timers;
};

NET_END_NAMESPACE

#endif
