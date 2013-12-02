#pragma once

#include <unordered_map>
#include "UdpPacketHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Add reliability to the UDP protocol 
 */
class NET_DLLREQ ReliableUdpPacketHandler: public UdpPacketHandler
{
public:
	int handleInputPacket(Packet &) override;

	/*!
	 \brief A new version of handleOutputPacket
	 \details The reliability add some penalty to the speed, so you must use reliable Packet wisely
	 \param output Packet to be sent
	 \param reliable whether or not this packet is valuable to you

	 \return -1 on failure, >0 otherwise
	 */
	int handleOutputPacket(Packet const &output, bool reliable);
	
protected:
	enum
	{
		RETRIEVE = 0,
		UNRELIABLE = 1
	};

	int	sendRetrievePacket(size_t id);
	int resendPacket(Packet &input);

	std::unordered_map<InetAddr, std::unordered_map<size_t, Packet>, InetAddr::HashInetAddr>	_sentPackets;
	std::unordered_map<InetAddr, size_t, InetAddr::HashInetAddr>						_lastreceivedPacketId;
};

NET_END_NAMESPACE
