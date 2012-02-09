#ifndef TIMERSOCKET_HPP_
#define TIMERSOCKET_HPP_

#include "NetHandler.hpp"
#include "Socket.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ TimerSocket : public Socket
{
public:
	TimerSocket(Handle handle, NetHandler &handler);
	NetHandler			&getTimeoutHandler();

private:
	NetHandler			&_nethandler;
};

NET_END_NAMESPACE

#endif /* SOCKET_HPP_ */

