#pragma once

#include "Net.hpp"
#include "GameLogic.hpp"
#include "PacketType.hpp"
#include "Player.hpp"

class Game;
class Ship;

class Client : public Net::SizeHeaderPacketHandler<>
{
  public:
    Client();
    virtual ~Client();
	virtual void		init();
	virtual int			handleInputPacket(Net::Packet &packet);
	void				setGame(Game &game);
	void				setId(uint8_t id);
	uint32_t			getId() const;
	std::string const 	&getName() const;
	uint32_t			getPacketId();
	void				resetPacketId();
	void				addPacket(uint32_t id, Net::Packet &packet);
	Game				*getGame() const;
	GameLogic			*getGameLogic() const;
	Net::Packet const	*getPacket(uint32_t id) const;

	double				getLatency() const;
	void				setLatency(double latency);
	uint32_t			getLastRecvId() const;
	void				setLastRecvId(uint32_t id);
	int					getRemoteAddr(Net::InetAddr &addr);
	void				setUDPAddr(Net::InetAddr &addr);
	Net::InetAddr const		&getUDPAddr() const;
	bool				isReady() const;
	std::list<Player*> const	&getPlayers() const;

  private:
	typedef std::list<std::pair<uint32_t, Net::Packet> >	packetsList;

	int			connection(Net::Packet &packet);
	int			listGame(Net::Packet &packet);
	int			connectGame(Net::Packet &packet);
	int			player(Net::Packet &packet);
	int			createGame(Net::Packet &packet);
	int			requireResource(Net::Packet &packet);
	int			gameState(Net::Packet &packet);
	int			demandPlayer(Net::Packet &packet);
	int			updatePlayer(Net::Packet &packet);
	int			removePlayer(Net::Packet &packet);

	int			sendError(Error::Type error);
	int			sendResources();

	uint8_t				_id;
	std::string			_name;
	Game				*_game;
	uint32_t			_idPacket;
	uint32_t			_idRecvPacket;
	uint32_t			_idShip;
	uint64_t			_nblatency;
	double				_latency;
	bool				_ready;
	packetsList			_packets;
	std::list<Player*>	_players;
	Net::InetAddr		_udpaddr;
};
