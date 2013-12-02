/*
 * UdpPacketHandler.h
 *
 *  Created on: Dec 2, 2011
 *      Author: snap
 */

#ifndef RINGBUFFERPACKETHANDLER_H_
#define RINGBUFFERPACKETHANDLER_H_

#include <stdexcept>
#include "PacketHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief PacketHandler with a string delimiter
 
 \tparam IOType Underlying connection type
 */
template <typename IOType = SocketStream>
class	RingBufferPacketHandler : public PacketHandler<IOType>
{
public:
	
	/*!
	 \brief Construct a RingBufferPacketHandler
	 \param deli Delimiter to delimit packet
	 */
	RingBufferPacketHandler(std::string const &deli) : PacketHandler<IOType>()
	{
		this->setDelimeter(deli);
	}
	
	int	handleInput(Socket &) override
	{	
		int				ret = 0;

		do
		{
			ret = this->_iohandler.recvPacket(this->_inpacket);
			if (ret == -1 && wouldBlock())
					return 1;
			if (ret > 0)
			{
				_tmp.assign(this->_inpacket.base(), this->_inpacket.size());

			}
		}
		while (!this->_iohandler.isBlocking());
		return ret;
	}

	/*!
	 \brief Change the delimiter
	 \details It can be risky to change the delimiter when you are receiving Packet
	 \param deli new delimeter
	 */
	void	setDelimiter(std::string const &deli)
	{
		if (deli.empty())
			throw std::logic_error("Delimeter cannot be an empty string");
		this->_delimiter = deli;
	}

private:
	std::string			_delimiter;
	std::string			_tmp;
};

NET_END_NAMESPACE

#endif /* UDPPACKETHANDLER_H_ */
