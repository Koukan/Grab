#pragma once

#include "Net.hpp"
#include "PacketType.hpp"

class Game;

class Server : public Net::PacketHandler<>
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

	std::string		_name;
	Game			*_game;
};
