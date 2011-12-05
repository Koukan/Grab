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

class SocketIO : public Socket
{
public:
	SocketIO();
	virtual ~SocketIO();

	int	sendmsg(Packet &packet, size_t index = 0, InetAddr *addr = 0, int flags = 0);
	int	recvmsg(Packet &packet, size_t index = 0, InetAddr *addr = 0, int flags = 0);
	int	send(const char *buff, size_t size, int flags = 0);
	int	recv(char *buff, size_t size, int flags = 0);
	virtual	int	send(Packet &packet, int flags = 0);
	virtual int	recv(Packet &packet, int flags = 0);
};

#endif /* HandleIO_HPP_ */
