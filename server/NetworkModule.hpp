#pragma once

#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "Client.hpp"
#include "UdpHandler.hpp"
#include "Singleton.hpp"

class NetworkModule : public Core::Module, public Net::Singleton<NetworkModule>
{
  public:
    NetworkModule();
    virtual ~NetworkModule();
	virtual void	init();
	virtual void	update(double elapsedTime);
	virtual void	destroy();
	virtual bool	handleCommand(Core::Command const &command);
	void			setPort(std::string const &port);
	void			addUDPClient(Client &player);
	void			removeUDPClient(Client &player);
	Client			*getClientByAddr(Net::InetAddr const &addr) const;
	void			sendTCPPacket(Net::Packet &packet, std::list<Client*> const &list, Client *player);

  private:
	struct	Method
	{
		std::string	name;
		void	(NetworkModule::*method)(Core::Command const &);
	};

	void		spawnCommand(Core::Command const &command);
	void		destroyCommand(Core::Command const &command);
	void		moveCommand(Core::Command const &command);
	void		sendUDPPacket(Net::Packet &packet,
					std::list<Client*> const &list,
					bool needId, Client *player);
	void		statusCommand(Core::Command const &command);
	void		startgameCommand(Core::Command const &command);
	void		rangeId(Core::Command const &command);
	void		resourceId(Core::Command const &command);
	void		sendPing();
	bool		gameExist(Game *);


	Net::Reactor						*_reactor;
	size_t								_pingupdate;
	Net::Acceptor<Client>				_acceptor;
	UdpHandler							_udp;
	std::string							_port;
	//Net::SetupNetwork					_init;
	std::map<Net::InetAddr, Client *>	_players;
};
