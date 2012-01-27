#include "PacketCommand.hpp"

PacketCommand::PacketCommand(std::string const &name,
							 Server &server, Net::Packet &packet)
	: Command(name), server(server),
	packet(*(new Net::Packet(packet)))
{
}

PacketCommand::~PacketCommand()
{
	delete &packet;
}
