/*
 * SocketDatagram.hpp
 *
 *  Created on: Nov 17, 2011
 *      Author: snap
 */

#ifndef HandleDATAGRAM_HPP_
#define HandleDATAGRAM_HPP_

#include "SocketIO.hpp"

class SocketDatagram: public SocketIO
{
public:
	SocketDatagram();
	~SocketDatagram();

	int	setup(InetAddr &addr, int protocol = IPPROTO_UDP);
	int	connect(InetAddr &addr);
	virtual int	send(Packet &packet, int flags = 0);
	virtual int	recv(Packet &packet, int flags = 0);

private:
	int	bind(InetAddr &addr);
};

#endif /* HandleDATAGRAM_HPP_ */
