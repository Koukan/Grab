#pragma once

#include <deque>
#include "Socket.hpp"
#include "Packet.hpp"


NET_BEGIN_NAMESPACE

/*!
 \brief Define the I/O operation on a socket
 */
class NET_DLLREQ SocketIO : public Socket
{
public:
	SocketIO();
	virtual ~SocketIO();

	static int const listSize = 50;

	/*!
	 \brief Raw write on the Socket

	 \param buff buffer of data to send
	 \param size size of the buffer
	 \param flags optional flags, cf man send

	 \return -1 on failure, >0 otherwise
	 */
	virtual int	send(const char *buff, size_t size, int flags = 0);
	/*!
	 \brief Raw read on the Socket

	 \param buff buffer to store date
	 \param size size of the buffer
	 \param flags optional flags, cf man recv

	 \return -1 on failure, >0 otherwise
	 */
	virtual int	recv(char *buff, size_t size, int flags = 0);
	/*!
	 \brief Send a Packet

	 \param packet Packet to send
	 \param flags optional flags, cf man send
	 \param size optional size to read

	 \return -1 on failure, >0 otherwise
	 */
	virtual	int	sendPacket(Packet &packet, int flags = 0, int size = -1);
	/*!
	 \brief Receive a Packet

	 \param packet Packet to store data
	 \param flags optional flags, cf man recv
	 \param size optional size to write

	 \return -1 on failure, >0 otherwise
	 */
	virtual int	recvPacket(Packet &packet, int flags = 0, int size = -1);
	/*!
	 \brief Send a list of Packet

	 \param packets A std::deque of packet
	 \param flags optional flags, cf man send
	 \details This function use sendPacket internally
	 \return -1 on failure, >0 otherwise
	 */
	virtual int sendPackets(std::deque<Packet> &packets, int flags = 0);

protected:
	char	_receivebuffer[4096];
};

NET_END_NAMESPACE
