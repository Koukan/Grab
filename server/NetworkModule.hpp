#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "Player.hpp"
#include "UdpHandler.hpp"
#include "Singleton.hpp"

class NetworkModule : public Module, public Singleton<NetworkModule>
{
  public:
    NetworkModule();
    virtual ~NetworkModule();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	virtual bool	handleCommand(Command const &command);
	void			setPort(std::string const &port);
	void			addUDPPlayer(Player &player);
	void			removeUDPPlayer(Player &player);
	Player			*getPlayerByAddr(Net::InetAddr const &addr) const;

  private:
	struct	Method
	{
		std::string	name;
		void	(NetworkModule::*method)(Command const &);
	};

	void		spawnCommand(Command const &command);
	void		destroyCommand(Command const &command);
	void		moveCommand(Command const &command);
	void		sendUDPPacket(Net::Packet &packet,
					std::list<Player*> const &list,
					bool needId, Player *player);
	void		sendTCPPacket(Net::Packet &packet, std::list<Player*> const &list, Player *player);
	void		statusCommand(Command const &command);
	void		startgameCommand(Command const &command);
	void		rangeId(Command const &command);
	void		sendPing();
	bool		gameExist(Game *);


	Net::Reactor						*_reactor;
	size_t								_pingupdate;
	Net::Acceptor<Player>				_acceptor;
	UdpHandler							_udp;
	std::string							_port;
	Net::SetupNetwork					_init;
	std::map<Net::InetAddr, Player *>	_players;
};
