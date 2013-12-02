#include "TimerSocket.hpp"

NET_USE_NAMESPACE

TimerSocket::TimerSocket(Handle handle, EventHandler &handler, size_t delay) : handler(handler), delay(delay)
{
	this->setHandle(handle);
}

