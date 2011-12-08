#if defined (_WIN32)

#include "WFMOPolicy.hpp"

NET_USE_NAMESPACE

WFMOPolicy::WFMOPolicy() : _size(0)
{
	for	(int i = 0; i < MAXIMUM_WAIT_OBJECTS; ++i)
	{
	   _handles[i] = ::WSACreateEvent();
	}
}

WFMOPolicy::~WFMOPolicy()
{
	for	(int i = 0; i < MAXIMUM_WAIT_OBJECTS; ++i)
	{
	   ::WSACloseEvent(_handles[i]);
	}
}

int		WFMOPolicy::registerHandler(Socket &socket, NetHandler &handler, int mask)
{
  size_t	index;
  SocketMap::iterator it = _map.find(socket.getHandle());
  if (it != _map.end())
    index = it->second;
  else if (!_emptySlot.empty())
  {
	index = _emptySlot.front();
	_emptySlot.pop();
	_map[socket.getHandle()] = index;
  }
  else if (_size < MAXIMUM_WAIT_OBJECTS - 1)
  {
    index = _size++;
	_map[socket.getHandle()] = index;
  }
  else
   return -1;
  _data[index].handler = &handler;
  _data[index].socket = &socket;
  long	flags = 0;
  if (mask & Reactor::READ)
	 flags |= FD_READ;
  if (mask & Reactor::ACCEPT)
	 flags |= FD_ACCEPT;
  if (mask & Reactor::WRITE)
	 flags |= FD_WRITE;
  return ((::WSAEventSelect(socket.getHandle(), _handles[index], flags) == SOCKET_ERROR) ? -1 : 0);
}

int		WFMOPolicy::removeHandler(Socket &socket)
{
  SocketMap::iterator it = _map.find(socket.getHandle());
  if (it == _map.end())
	return -1;
  size_t	index = it->second;
  //_handlers[index] = 0;
  _emptySlot.push(index);
  if (_size == index + 1)
	  _size--;
  return ((::WSAEventSelect(socket.getHandle(), _handles[index], 0) == SOCKET_ERROR) ? -1 : 0);
}

int	WFMOPolicy::waitForEvent(int timeout)
{
	DWORD	index;
	WSANETWORKEVENTS netEvent;

	while (_wait)
	{
		index = ::WSAWaitForMultipleEvents(_size, _handles, FALSE, this->handleTimers(timeout), FALSE);
		while (index != WSA_WAIT_FAILED && index != WSA_WAIT_TIMEOUT)
		{
		  this->dispatchEvent(index, &netEvent);
		  index = ::WSAWaitForMultipleEvents(_size, _handles, FALSE, 0, FALSE);
		}
		if (index == WSA_WAIT_FAILED)
		   return -1;
		else if (index == WSA_WAIT_TIMEOUT && timeout == 0)
		  return 0;
		if (_size == 0)
		  _wait = false;
	}
  return 0;
}

void	WFMOPolicy::dispatchEvent(DWORD index, LPWSANETWORKEVENTS netEvent)
{
  index -= WSA_WAIT_EVENT_0;
  ::WSAEnumNetworkEvents(_data[index].socket->getHandle(), 0, netEvent);
  ::WSAResetEvent(_handles[index]);
  if (netEvent->lNetworkEvents & FD_CLOSE)
     _data[index].handler->handleClose(*(_data[index].socket));
  else
  {
	if (netEvent->lNetworkEvents & FD_WRITE)
		_data[index].handler->handleOutput(*(_data[index].socket));
	if ((netEvent->lNetworkEvents & FD_READ || netEvent->lNetworkEvents & FD_ACCEPT)
		&& _data[index].handler->handleInput(*(_data[index].socket)) <= 0)
		_data[index].handler->handleClose(*(_data[index].socket));
  }
}
#endif
