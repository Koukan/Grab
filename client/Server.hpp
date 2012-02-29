#pragma once

#include "Net.hpp"
#include "PacketType.hpp"

class Game;

class Server : public Net::SizeHeaderPacketHandler<>
{
  public:
    Server();
    virtual ~Server();
	virtual int		handleInputPacket(Net::Packet &packet);
	void			setGame(Game &game);

  private:
	bool			treatEtablishedPacket(Net::Packet &packet);
	bool			treatGamePacket(Net::Packet &packet);
	bool			treatEndListGamePacket(Net::Packet &packet);
	bool			treatPlayerPacket(Net::Packet &packet);
	bool			treatGameStatePacket(Net::Packet &packet);
	bool			treatErrorPacket(Net::Packet &packet);
	bool			rangeId(Net::Packet &packet);
	bool			resourceId(Net::Packet &packet);
	bool			demandPlayerPacket(Net::Packet &packet);
	bool			addPlayerPacket(Net::Packet &packet);
	bool			removePlayerPacket(Net::Packet &packet);

	std::string		_name;
	Game			*_game;
};
