#pragma once

#include "Net.hpp"
#include "GameLogic.hpp"
#include "PacketType.hpp"

class Game;
class Ship;

class Player : public Net::PacketHandler<>
{
  public:
    Player();
    virtual ~Player();
	virtual void		init();
	virtual int			handleInputPacket(Net::Packet &packet);
	void				setGame(Game &game);
	void				setId(uint8_t id);
	uint32_t			getId() const;
	std::string const 	&getName() const;
	uint32_t			getPacketId();
	void				resetPacketId();
	Ship				*getShip() const;
	void				setShip(Ship *ship);
	void				addPacket(uint32_t id, Net::Packet &packet);
	GameLogic       	&getGameLogic();
	Net::Packet const	*getPacket(uint32_t id) const;

	uint64_t			getLatency() const;
	void				setLatency(uint64_t latency);

  private:
	typedef std::list<std::pair<uint32_t, Net::Packet> >	packetsList;

	int			connection(Net::Packet &packet);
	int			listGame(Net::Packet &packet);
	int			connectGame(Net::Packet &packet);
	int			player(Net::Packet &packet);
	int			createGame(Net::Packet &packet);
	int			requireResource(Net::Packet &packet);

	int			sendError(Error::Type error);
	int			sendResources();

	uint8_t			_id;
	std::string		_name;
	Game			*_game;
	Ship			*_ship;
	uint32_t		_idPacket;
	uint32_t		_idShip;
	uint64_t		_latency;
	packetsList		_packets;
};
