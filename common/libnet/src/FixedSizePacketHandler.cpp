#include <stdexcept>
#include "FixedSizePacketHandler.hpp"

NET_USE_NAMESPACE

FixedSizePacketHandler::FixedSizePacketHandler(size_t packetSize)
	: _packetSize(packetSize)
{
}

FixedSizePacketHandler::~FixedSizePacketHandler()
{
}

int				FixedSizePacketHandler::handleInput(Net::Socket &socket)
{
	int			ret = 0;

	do
	{
		ret = this->_iohandler.recvPacket(this->_inpacket);
		if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
			return 1;
		if (ret > 0)
		{
			size_t	i;
			for (i = 0; i + _packetSize <= _inpacket.size(); i += _packetSize)
			{
				Net::Packet		packet;
				packet.addBuffer(&_inpacket.base()[i], _packetSize);
				this->handleInputPacket(packet);
			}
			if (i > _inpacket.size())
			{
				size_t			size = _inpacket.size() - i;
				std::string		str;
				str.append(&_inpacket.base()[i], size);
				_inpacket.reset();
				_inpacket.addBuffer(str.c_str(), size);
			}
			else if (i != 0)
				_inpacket.reset();
		}
	} while (!this->_iohandler.isBlocking());
	return ret;
}

int				FixedSizePacketHandler::handleOutputPacket(Net::Packet &output)
{
	int		size = _packetSize - output.size();
	if (size > 0)
		output.addBuffer(std::string(size, '\0').c_str(), size);
	return PacketHandler::handleOutputPacket(output);
}

size_t			FixedSizePacketHandler::getPacketSize() const
{
	return _packetSize;
}

void			FixedSizePacketHandler::setPacketSize(size_t size)
{
	if (size == 0)
		throw std::logic_error("Packet size must be > 0");
	_packetSize = size;
}