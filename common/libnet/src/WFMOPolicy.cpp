#if defined (WIN32)

#include "WFMOPolicy.hpp"

NET_USE_NAMESPACE

WFMOPolicy::WFMOPolicy() : _size(1)
{
	::memset(_handles, 0, MAXIMUM_WAIT_OBJECTS * sizeof(HANDLE));
	::memset(_data, 0, MAXIMUM_WAIT_OBJECTS * sizeof(wfmopolicydata));
	_handles[0] = ::WSACreateEvent();
}

WFMOPolicy::~WFMOPolicy()
{
}

int		WFMOPolicy::attributeIndex(HANDLE handle)
{
	int index = -1;

	auto it = _map.find(handle);
	if (it != _map.end())
		index = it->second;
	else if (_size < MAXIMUM_WAIT_OBJECTS - 1)
		index = _size++;
	if (index != -1 && it == _map.end())
	{
		_map[handle] = index;
		_handles[index] = handle;
	}
	return index;
}

bool		WFMOPolicy::registerHandler(HANDLE handle, EventHandler &handler)
{
	int index = this->attributeIndex(handle);
	if (index == -1)
		return false;
	_data[index].handler = &handler;
	_data[index].socket = new Socket(handle);
	_data[index].isSocket = false;
	return true;
}

bool		WFMOPolicy::registerHandler(Socket &socket, EventHandler &handler, int mask)
{
  int	index = this->attributeIndex(socket.getAssociatedHandle());
  if (index == -1)
	return false;
  _data[index].handler = &handler;
  _data[index].socket = &socket;
  _data[index].isSocket = true;
  long	flags = FD_CLOSE;
  if (mask & Reactor::READ)
	 flags |= FD_READ;
  if (mask & Reactor::ACCEPT)
	 flags |= FD_ACCEPT;
  if (mask & Reactor::WRITE)
	 flags |= FD_WRITE;
  return (::WSAEventSelect(socket.getHandle(), _handles[index], flags) != SOCKET_ERROR);
}

bool		WFMOPolicy::removeHandler(Socket &socket)
{
	auto it = _map.find(socket.getAssociatedHandle());
	if (it == _map.end())
		return false;
	size_t	index = it->second;
	_map.erase(it);
	int ret = (socket.getHandle() != INVALID_HANDLE) ? ::WSAEventSelect(socket.getHandle(), _handles[index], 0) : 0; 
	_handles[index] = NULL;
	_data[index].handler = nullptr;
	_data[index].socket = nullptr;
	for (size_t i = index + 1; i < _size; ++i)
	{
		_map[_handles[i]] = i - 1;
		_handles[i - 1] = _handles[i];
		_data[i - 1] = _data[i];
	}
   _size--;
	return (ret == 0);
}

int	WFMOPolicy::waitForEvent(int timeout)
{
	DWORD	index;
	WSANETWORKEVENTS netEvent;

	while (_wait)
	{
		index = ::WaitForMultipleObjectsEx(_size, _handles, FALSE, (timeout == -1) ? INFINITE : timeout, TRUE);
		if (!_wait)
			return 0;
		while (index != WAIT_FAILED && index != WAIT_TIMEOUT && index != WAIT_IO_COMPLETION && _wait)
		{
		  this->dispatchEvent(index - WSA_WAIT_EVENT_0, &netEvent);
		  index = ::WaitForMultipleObjects(_size, _handles, FALSE, 0);
		}
		if (index == WAIT_FAILED)
		   return -1;
		else if (index == WAIT_TIMEOUT && timeout == 0)
		  return 0;
		if (_size == 0)
		  _wait = false;
	}
  return 0;
}

void	WFMOPolicy::dispatchEvent(DWORD index, LPWSANETWORKEVENTS netEvent)
{
  if (_data[index].handler == nullptr || _data[index].socket == nullptr)
	return ;
  if (!_data[index].isSocket)
  {
	_data[index].handler->handleInput(*(_data[index].socket));
	return ;
  }
  ::WSAEnumNetworkEvents(_data[index].socket->getHandle(), _handles[index], netEvent);
  if (netEvent->lNetworkEvents & FD_CLOSE)
     _data[index].handler->handleClose(*(_data[index].socket));
  else if ((netEvent->lNetworkEvents & FD_READ || netEvent->lNetworkEvents & FD_ACCEPT)
		&& _data[index].handler->handleInput(*(_data[index].socket)) <= 0)
		_data[index].handler->handleClose(*(_data[index].socket));
  else if (netEvent->lNetworkEvents & FD_WRITE && _data[index].handler->handleOutput(*(_data[index].socket)) <= 0)
		_data[index].handler->handleClose(*(_data[index].socket));
}

void CALLBACK WFMOPolicy::TimerAPCProc(LPVOID lpArg, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	 WFMOPolicy::timerdata *timer = reinterpret_cast<WFMOPolicy::timerdata *>(lpArg);

	 LARGE_INTEGER	time;
	 time.LowPart = dwTimerLowValue;
	 time.HighPart = dwTimerHighValue;
	 if (timer->lastTick.QuadPart == 0)
		 timer->lastTick = time;
	 timer->handler->handleTimeout((time.QuadPart - timer->lastTick.QuadPart) / 10000);
	 timer->lastTick = time;
}

uint32_t		WFMOPolicy::scheduleTimer(EventHandler &handler, size_t delay, bool repeat)
{
 	HANDLE timer = CreateWaitableTimer(NULL, FALSE, NULL);
	LARGE_INTEGER   liDueTime;
	liDueTime.QuadPart = -(delay * 10000);
	WFMOPolicy::timerdata *timerdata = new WFMOPolicy::timerdata;
	timerdata->handler = &handler;
	timerdata->lastTick.QuadPart = 0;
	if (SetWaitableTimer(timer, &liDueTime, (repeat ) ? delay : 0, TimerAPCProc, timerdata, FALSE) == FALSE)
		return 0;
	auto id = this->getTimerId();
	_timers[id] = std::make_pair(timer, timerdata);
	return id;
}

bool			WFMOPolicy::cancelTimer(uint32_t timerId)
{
	auto it = _timers.find(timerId);
  	if (it == _timers.end())
		return false;
	CancelWaitableTimer(it->second.first);
	CloseHandle(it->second.first);
	delete it->second.second;
	return true;
}

#endif
