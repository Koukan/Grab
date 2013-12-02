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

/*!
 \brief The UDP version of the Socket
 */
class NET_DLLREQ SocketDatagram: public SocketIO
{
public:
	SocketDatagram();
	~SocketDatagram();

	int	setup(InetAddr const &addr, bool bind = true, int protocol = IPPROTO_UDP);

	/*!
	 \brief Connect the SocketDatagram to a specific address
	 \details This function avoid to copy the same address to the kernel land every time
	 \details If no address is specified in the Packet and the SocketDatagram is connected then the packet is sent to this address
	 \param addr Default address to send Packet

	 \return -1 on failure, >0 otherwise
	 */
	int	connect(InetAddr const &addr);
	/*!
	 \brief Check if the SocketDatagram is connected

	 \return True if connected, False otherwise
	 */
	bool isConnected() const;
	/*!
	 \brief Join a multicast group 
	 \details The address can be IPV4 or IPV6
	 \param addr Address of the multicast group
	 \return -1 on failure, >0 otherwise
	 */
	int	join(InetAddr const &addr);
	/*!
	 \brief Leave a multicast group
	 \details The address can be IPV4 or IPV6
	 \param addr Address of the multicast group

	 \return -1 on failure, >0 otherwise
	 */
	int	leave(InetAddr const &addr);
	/*!
	 \brief Set the TTL (IPV4) or the hop (IPV6)

	 \param value TTL
	 \param addr Address of the multicast group, needed to determine IP version

	 \return -1 on failure, >0 otherwise
	 */
	int	setTTLMulticast(uint32_t value, InetAddr const &addr);
	/*!
	  \brief Enable or disable broadcasting on the socket

	  \param boolean to enable or disable the option
	  \return -1 on failure, >0 otherwise
	  */
	int broadcast(bool flag = true);

	int	sendPacket(Packet &packet, int flags = 0, int size = -1) override;
	int	recvPacket(Packet &packet, int flags = 0, int size = -1) override;

private:
	int	bind(InetAddr const &addr);

	bool		_connected;
};

NET_END_NAMESPACE

#endif /* SOCKETDATAGRAM_HPP_ */
