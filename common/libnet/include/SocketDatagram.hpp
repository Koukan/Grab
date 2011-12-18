/*
 * SocketDatagram.hpp
 *
 *  Created on: Nov 17, 2011
 *      Author: snap
 */

#ifndef SOCKETDATAGRAM_HPP_
#define SOCKETDATAGRAM_HPP_

#include "SocketIO.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ SocketDatagram: public SocketIO
{
public:
	SocketDatagram();
	~SocketDatagram();

	int	setup(InetAddr const &addr, bool bind = true, int protocol = IPPROTO_UDP);
	int	connect(InetAddr const &addr);

	int	join(InetAddr const &addr);
	int	leave(InetAddr const &addr);
	int	setTTLMulticast(uint32_t value, InetAddr const &addr);

	virtual int	send(Packet &packet, int flags = 0);
	virtual int	recv(Packet &packet, int flags = 0);

private:
	int	bind(InetAddr const &addr);
};

NET_END_NAMESPACE

#endif /* SOCKETDATAGRAM_HPP_ */
