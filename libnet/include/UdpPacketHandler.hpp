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

NET_BEGIN_NAMESPACE

class NET_DLLREQ UdpPacketHandler: public PacketHandler<SocketDatagram>
{
public:
	UdpPacketHandler();
	~UdpPacketHandler();

	virtual int handleInput(Socket &);
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
