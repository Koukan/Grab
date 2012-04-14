#include "UdpHandler.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "DestroyCommand.hpp"

UdpHandler::UdpHandler() : _lastPacketId(0), _latency(0), _nblatency(0)
{
	this->enableWhitelist(true);
}

UdpHandler::~UdpHandler()
{
}

void		UdpHandler::init()
{
	this->_reactor->registerHandler(this->getIOHandler(), *this, Net::Reactor::READ);
}

int     	UdpHandler::handleClose(Net::Socket &)
{
	return 1;
}

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	static UdpHandler::functions methods[] = {
			{&UdpHandler::spawn, true},
			{&UdpHandler::destroy, true},
			{&UdpHandler::move, false},
			{0, false},
			{&UdpHandler::statement, false},
			{&UdpHandler::retrieve, false},
			{&UdpHandler::ping, false},
			{&UdpHandler::pong, false},
			{&UdpHandler::fireState, true},
			{&UdpHandler::updateCannon, true},
			{&UdpHandler::launchGrab, true},
			{&UdpHandler::deadPlayer, true},
			{0, false},
			{&UdpHandler::bonus, true},
			{&UdpHandler::auraActive, true}
	};
	uint64_t			time;
	uint8_t				type;

	if (packet.size() < 9)
		return 1;
	packet >> time;
	packet >> type;

	if (type < sizeof(methods) / sizeof(*methods) && methods[type].func != NULL)
	{
		if (methods[type].needId)
		{
			uint32_t	id_packet;
			packet >> id_packet;
			std::cout << "receive packet with id : " << id_packet << std::endl;
			this->testPacketId(id_packet);
		}
		return (this->*methods[type].func)(packet, time);
	}
	return 1;
}

int			UdpHandler::spawn(Net::Packet &packet, uint64_t)
{
	if (packet.size() != 29)
		return 1;
	GameCommand *gc = new GameCommand("spawn");
	packet >> gc->idResource;
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &packet, uint64_t)
{
	uint32_t	idchild;
	DestroyCommand *gc = new DestroyCommand("destroy");
	for (size_t	left = packet.size() - 13; left >= sizeof(uint32_t); left -= sizeof(uint32_t))
	{
		packet >> idchild;
		gc->ids.push_back(idchild);
	}
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::move(Net::Packet &packet, uint64_t time)
{
	uint32_t	idObject;

	packet >> idObject;
	std::map<uint32_t, uint64_t>::iterator it = _idmoves.find(idObject);
	if (it == _idmoves.end())
		it = _idmoves.insert(std::make_pair(idObject, time)).first;
	if (it->second <= time)
	{
		it->second = time;
		GameCommand *gc = new GameCommand("move");
		gc->idObject = idObject;
		packet >> gc->x;
		packet >> gc->y;
		packet >> gc->vx;
		packet >> gc->vy;
	//gc->x += gc->vx * (this->_latency / 1000);
	//gc->y += gc->vy * (this->_latency / 1000);
		Core::CommandDispatcher::get().pushCommand(*gc);
	}
	return 1;
}

int			UdpHandler::score(Net::Packet &, uint64_t)
{
	return 1;
}

int			UdpHandler::statement(Net::Packet &, uint64_t)
{
	return 1;
}

int         UdpHandler::retrieve(Net::Packet &packet, uint64_t)
{
	uint32_t	id;
	packet >> id;
	NetworkModule::get().retrievePacket(id);
	return 1;
}

int         UdpHandler::ping(Net::Packet &, uint64_t time_recv)
{
	Net::Packet     pong(9);
	pong << static_cast<uint64_t>(time_recv);
	pong << static_cast<uint8_t>(UDP::PONG);
	NetworkModule::get().sendPacketUDP(pong);
	Net::Packet     pong2(9);
	pong2 << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	pong2 << static_cast<uint8_t>(UDP::PING);
	NetworkModule::get().sendPacketUDP(pong2);
	return 1;
}

int         UdpHandler::pong(Net::Packet &, uint64_t time_recv)
{
	_nblatency++;
	_latency = (_latency * _nblatency + ((Net::Clock::getMsSinceEpoch() - time_recv) / 2)) / (_nblatency + 1);
	return 1;
}

int			UdpHandler::fireState(Net::Packet &packet, uint64_t)
{
	uint8_t		n;
	GameCommand *gc = new GameCommand("ServerFire");
	packet >> gc->idObject;
	packet >> n;
	gc->idResource = n;
	gc->score = _lastPacketId;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::updateCannon(Net::Packet &packet, uint64_t)
{
	uint8_t		n;
	GameCommand *gc = new GameCommand("ServerCannon");
	packet >> gc->idObject;
	packet >> n;
	gc->idResource = n;
	if (packet.size() > 22)
	{
		packet >> gc->x;
		packet >> gc->y;
		packet >> gc->data;
	}
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::launchGrab(Net::Packet &packet, uint64_t)
{
	uint8_t		n;
	GameCommand *gc = new GameCommand("ServerGrab");
	packet >> gc->idObject;
	packet >> n;
	gc->idResource = n;
	packet >> gc->x;
	packet >> gc->y;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::deadPlayer(Net::Packet &packet, uint64_t)
{
	GameCommand	*gc = new GameCommand("killPlayer");
	packet >> gc->idObject;
	packet >> gc->boolean;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::bonus(Net::Packet &packet, uint64_t)
{	
	GameCommand	*gc = new GameCommand("bonus");
	packet >> gc->idObject;
	gc->boolean = false;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::auraActive(Net::Packet &packet, uint64_t)
{	
	GameCommand	*gc = new GameCommand("aura");
	packet >> gc->idObject;
	Core::CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

bool		UdpHandler::testPacketId(uint32_t id)
{
	if (id > _lastPacketId)
	{
		++_lastPacketId;
		for (; _lastPacketId != id; ++_lastPacketId)
		{
			Net::Packet	packet(13);
			packet << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
			packet << static_cast<uint8_t>(UDP::RETRIEVE);
			packet << _lastPacketId;
			this->handleOutputPacket(packet);
			std::cout << "ask for packet id : " << _lastPacketId << std::endl;
		}
		return true;
	}
	return false;
}
