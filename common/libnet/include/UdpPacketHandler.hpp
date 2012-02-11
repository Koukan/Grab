/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef UDPPACKETHANDLER_H_
#define UDPPACKETHANDLER_H_

#include <set>
#include "PacketHandler.hpp"
#include "SocketDatagram.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ UdpPacketHandler: public PacketHandler<SocketDatagram>
{
public:
	UdpPacketHandler();
	~UdpPacketHandler();

	virtual int handleInput(Socket &);
	virtual int handleOutput(Socket &);

	void	enableWhitelist(bool enable);
	void	addAddr(InetAddr const &addr);
	void	removeAddr(InetAddr const &addr);
	void	clearAddr();

private:
	bool				_enableWhitelist;
	std::set<InetAddr>	_whitelist;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
