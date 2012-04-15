#pragma once

#include <map>
#include <string>
#include "Module.hpp"
#include "Net.hpp"
#include "UdpHandler.hpp"
#include "Server.hpp"
#include "Singleton.hpp"
#include "GameCommand.hpp"

class NetworkModule : public Core::Module, public Net::Singleton<NetworkModule>
{
  public:
	NetworkModule();
	virtual ~NetworkModule();
	virtual void		init();
	virtual bool		connect();
	virtual void		update(double elapsedTime);
	virtual void		destroy();
	virtual bool		handleCommand(Core::Command const &command);
	void				setName(std::string const &name);
	void				setPort(std::string const &port);
	void				setIP(std::string const &ip);
	std::string	const	&getName() const;
	std::string const	&getPort() const;
	std::string const	&getIP() const;

	void		setServer(Server *server);
	void		sendPacketUDP(Net::Packet &packet, bool needId = false);
	void		retrievePacket(uint32_t id);

  private:

// Command UDP

	void		retrieveCommand(Core::Command const &command);
	void		moveCommand(Core::Command const &command);
	void		spawnCommand(Core::Command const &command);
	void		fireCommand(Core::Command const &command);
	void		launchGrab(Core::Command const &command);
	void		updateCannon(Core::Command const &command);
	void		deadPlayer(Core::Command const &command);
	void		bonus(Core::Command const &command);
	void		auraActivated(Core::Command const &command);

// Command TCP

	void		connectionCommand(Core::Command const &command);
	void		createGameCommand(Core::Command const &command);
	void		listGamesCommand(Core::Command const &command);
	void		connectGameCommand(Core::Command const &command);
	void		playerCommand(Core::Command const &command);
	void		demandPlayerCommand(Core::Command const &command);
	void		unBindPlayerCommand(Core::Command const &command);
	void		updatePlayerCommand(Core::Command const &command);
	void		readyCommand(Core::Command const &command);
	void		mapChoiceCommand(Core::Command const &command);
	void		reBindCommand(Core::Command const &command);

	struct	Method
	{
		std::string	const name;
	  void	(NetworkModule::*method)(Core::Command const &);
	};

	bool					_initudp;
	uint32_t				_sentPacketId;
  	Net::DefaultSyncPolicy	_reactor;
	UdpHandler	       		_udp;
	Net::Connector<Server>	_connector;
	std::string				_name;
	std::string	       		_port;
	std::string	       		_ip;
	Net::InetAddr			_addr;
	std::map<uint32_t, Net::Packet>	_packets;
	Server*					_server;
};
