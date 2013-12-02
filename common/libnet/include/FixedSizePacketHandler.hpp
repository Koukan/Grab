#pragma once

#include "NetDef.hpp"
#include "PacketHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
	\brief PacketHandler for fixed size packets
*/
class NET_DLLREQ FixedSizePacketHandler : public PacketHandler<SocketStream>
{
  public:
	/*!
		\brief Construct a FixedSizePacketHandler
		\param packetSize Size of packets
	*/
	FixedSizePacketHandler(size_t packetSize);
    virtual ~FixedSizePacketHandler();

	int			handleInput(Net::Socket &socket) override;
	int			handleOutputPacket(Net::Packet &output) override;

	/*!
		\brief Gets the packet size
		\return Size of packets
	*/
	size_t		getPacketSize() const;
	/*!
		\brief Sets the packet size
		\param size Size of packets
	*/
	void		setPacketSize(size_t size);

private:
	size_t		_packetSize;
};

NET_END_NAMESPACE