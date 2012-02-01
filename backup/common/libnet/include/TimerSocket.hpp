/*
 * Socket.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef TIMERSOCKET_HPP_
#define TIMERSOCKET_HPP_

#include "NetHandler.hpp"
#include "Socket.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ TimerSocket : public Socket
{
public:
	TimerSocket(Handle handle, NetHandler &handler);
	NetHandler			&getNetHandler();

private:
	NetHandler			&_nethandler;
};

NET_END_NAMESPACE

#endif /* SOCKET_HPP_ */
