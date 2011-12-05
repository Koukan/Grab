/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef UDPPACKETHANDLER_H_
#define UDPPACKETHANDLER_H_

#include "PacketHandler.hpp"
#include "SocketDatagram.hpp"

class UdpPacketHandler: public PacketHandler<SocketDatagram>
{
public:
	UdpPacketHandler();
	~UdpPacketHandler();

	virtual int handleInput(Socket &);
};

#endif /* UDPPACKETHANDLER_H_ */
