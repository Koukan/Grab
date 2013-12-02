/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef UDPPACKETHANDLER_H_
#define UDPPACKETHANDLER_H_

#include <set>
#include "Reactor.hpp"
#include "PacketHandler.hpp"
#include "SocketDatagram.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief PacketHandler designed to handle UDP Packet
 */
class NET_DLLREQ UdpPacketHandler: public PacketHandler<SocketDatagram>
{
public:
	UdpPacketHandler();

	int handleInput(Socket &) override;

	/*!
	 \brief Prepare the socket for UDP operation
	 \details Due to the connectionless nature of UDP, this PacketHandler does not work the Acceptor or the Connector, therefore setup() must be called manually
	 \details param listen with a true value is only useful on the server side.
	 \param addr Address to listen or 'connect' 
	 \param reactor A reference to Reactor
	 \param listen Whether or not this socket listen to UDP packet
	 \return false on failure, true otherwise
	 */
	bool	setup(InetAddr const &addr, Reactor &reactor, bool listen = false);
	/*!
	\brief send Packet to a specified destination
	\param Packet to send
	\param Internet Address destination
	*/
	int 	send(Packet const &packet, InetAddr const &dest);
	/*!
	 \brief Enable or disable
	 \details If the whitelist is enabled only added addresse call handlePacket
	 \param enable boolean to enable or disable whitelist
	 */
	void	enableWhitelist(bool enable);
	/*!
	 \brief Add an address to the whitelist

	 \param addr address to add
	 */
	void	addAddr(InetAddr const &addr);
	/*!
	 \brief Remove an address from the whitelist

	 \param addr address to remove
	 */
	void	removeAddr(InetAddr const &addr);
	/*!
	 \brief Empty the whitelist
	 */
	void	clearAddr();

protected:
	bool				_enableWhitelist;
	std::set<InetAddr>	_whitelist;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
