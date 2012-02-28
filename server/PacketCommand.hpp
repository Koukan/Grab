#pragma once

#include <string>
#include "Net.hpp"
#include "Client.hpp"
#include "Command.hpp"

class PacketCommand : public Core::Command
{
  public:
    PacketCommand(std::string const &name,
				  Client &player, Net::Packet &packet);
    virtual ~PacketCommand();

	Client			&player;
	Net::Packet		&packet;
};
