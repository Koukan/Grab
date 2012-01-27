/*
 * SocketIO.hpp
 *
 *  Created on: Nov 4, 2011
 *      Author: snap
 */

#ifndef HandleIO_HPP_
#define HandleIO_HPP_

#include "Socket.hpp"
#include "Packet.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ SocketIO : public Socket
{
public:
	SocketIO();
	virtual ~SocketIO();

	int	sendmsg(Packet &packet, size_t index = 0, InetAddr *addr = 0, int flags = 0);
	int	recvmsg(Packet &packet, size_t index = 0, InetAddr *addr = 0, int flags = 0);
	int	send(const char *buff, size_t size, int flags = 0);
	int	recv(char *buff, size_t size, int flags = 0);
	virtual	int	sendPacket(Packet &packet, int flags = 0, int size = -1);
	virtual int	recvPacket(Packet &packet, int flags = 0, int size = -1);
};

NET_END_NAMESPACE

#endif /* HandleIO_HPP_ */
