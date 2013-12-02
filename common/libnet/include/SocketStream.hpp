#pragma once

#include <string>
#include "SocketIO.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief The TCP version of the Socket
 */
class NET_DLLREQ SocketStream : public SocketIO
{
public:
	SocketStream();
	~SocketStream();

	int		close() override;
	/*!
	 \brief Allow to close properly the TCP connection 

	 \param flags optional flags

	 \return -1 on failure, >0 otherwise
	 */
	int		shutdown(int flags = SHUT_RDWR);
	/*!
	 \brief	Enable or Disable Nagle algorithm

	 \param bool of waiting 

	 \return -1 on failure, >0 otherwise
	 */
	int		setNagleEnable(bool flag);
	/*!
	 \brief	Retrieve the round trip time of the connection

	 \return -1 on failure, the value of the RTT in ms otherwise
	 */
	int		getRoundTripTime();
	/*!
	 \brief Send a file across the network usinf OS specific sendfile() function 
	 \details This the most efficient way to send a file since copy to the userland is avoided
	 \details This function blocks until finished
	 \param path Path to the file

	 \return -1 on failure, >0 otherwise
	 */
	int		sendfile(std::string const &path);
	int		sendPackets(std::deque<Packet> &packets, int flags = 0) override;
};

NET_END_NAMESPACE

