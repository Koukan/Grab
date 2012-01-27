#pragma once

#include <string>
#include "Net.hpp"
#include "Server.hpp"
#include "Command.hpp"

class PacketCommand : public Command
{
  public:
    PacketCommand(std::string const &name,
				  Server &server, Net::Packet &packet);
    virtual ~PacketCommand();

	Server			&server;
	Net::Packet		&packet;
};
