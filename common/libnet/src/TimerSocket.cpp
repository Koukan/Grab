#include "TimerSocket.hpp"

NET_USE_NAMESPACE

TimerSocket::TimerSocket(Handle handle, NetHandler &handler) : _nethandler(handler)
{
	this->setHandle(handle);
}

NetHandler	&TimerSocket::getTimeoutHandler()
{
	return _nethandler;
}

