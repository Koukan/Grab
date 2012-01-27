#include "PacketCommand.hpp"

PacketCommand::PacketCommand(std::string const &name,
							 Player &player, Net::Packet &packet)
	: Command(name), player(player),
	packet(*(new Net::Packet(packet)))
{
}

PacketCommand::~PacketCommand()
{
	delete &packet;
}
