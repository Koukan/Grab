#include "ReliableUdpPacketHandler.hpp"

NET_USE_NAMESPACE

int	ReliableUdpPacketHandler::handleInputPacket(Packet &input)
{
	size_t	id;

	input >> id;
	if (id == ReliableUdpPacketHandler::RETRIEVE)
		return this->resendPacket(input);
	else if (id == ReliableUdpPacketHandler::UNRELIABLE)
		return 1;
	size_t last = _lastreceivedPacketId[input.getAddr()];
	_lastreceivedPacketId[input.getAddr()] = id;
	for (;id > last + 1; --id)
		this->sendRetrievePacket(id - 1);
	return 1;
}

int ReliableUdpPacketHandler::sendRetrievePacket(size_t id)
{
	Packet	retrieve;

	retrieve << ReliableUdpPacketHandler::RETRIEVE;
	retrieve << id;
	return this->PacketHandler<SocketDatagram>::handleOutputPacket(retrieve);
}

int ReliableUdpPacketHandler::resendPacket(Packet &input)
{
	size_t	id;

	input >> id;
	auto it = _sentPackets.find(input.getAddr());
	if (it == _sentPackets.end())
		return 1;
	auto at = it->second.find(id);
	if (at == it->second.end())
		return 1;
	return this->PacketHandler<SocketDatagram>::handleOutputPacket(at->second);
}

int ReliableUdpPacketHandler::handleOutputPacket(Packet const &output, bool reliable)
{
	size_t id = (reliable) ? _lastreceivedPacketId[output.getAddr()]++ : ReliableUdpPacketHandler::UNRELIABLE;
	Net::Packet cpy(output);
	cpy.wr_ptr(0);
	cpy << id;
	if (reliable)
		_sentPackets[output.getAddr()].insert(std::make_pair(id, cpy));
	return this->PacketHandler<SocketDatagram>::handleOutputPacket(cpy);
}
