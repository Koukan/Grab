#pragma once

#include <string>
#include "Net.hpp"
#include "Player.hpp"
#include "Command.hpp"

class PacketCommand : public Command
{
  public:
    PacketCommand(std::string const &name,
				  Player &player, Net::Packet &packet);
    virtual ~PacketCommand();

	Player			&player;
	Net::Packet		&packet;
};
