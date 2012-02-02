#include "UdpHandler.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

UdpHandler::UdpHandler() : _lastPacketId(static_cast<uint32_t>(-1)), _latency(0)
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

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	static int			(UdpHandler::* const methods[])(Net::Packet&, uint64_t) = {
			&UdpHandler::spawn,
			&UdpHandler::destroy,
			&UdpHandler::move,
			NULL,
			NULL,
			&UdpHandler::retrieve,
			&UdpHandler::ping,
			&UdpHandler::pong
	};
	uint64_t			time;
	uint8_t				type;

	if (packet.size() < 9)
		return 0;
	packet >> time;
	packet >> type;

	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
		return (this->*methods[type])(packet, time);
	return 0;
}

int			UdpHandler::spawn(Net::Packet &packet, uint64_t)
{
	uint32_t	id_packet;

	if (packet.size() != 29)
		return 0;
	packet >> id_packet;
	this->testPacketId(id_packet);
	GameCommand *gc = new GameCommand("spawn");
	packet >> gc->idResource;
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &packet, uint64_t)
{
	uint32_t	id_packet;

	packet >> id_packet;
	this->testPacketId(id_packet);
	GameCommand *gc = new GameCommand("destroy");
	packet >> gc->idObject;
	CommandDispatcher::get().pushCommand(*gc);	
	return 1;
}

int			UdpHandler::move(Net::Packet &packet, uint64_t)
{
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	CommandDispatcher::get().pushCommand(*gc);
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

int         UdpHandler::retrieve(Net::Packet &, uint64_t)
{
	return 1;
}

int         UdpHandler::ping(Net::Packet &, uint64_t time_recv)
{
	Net::Packet     pong(18);
	pong << static_cast<uint64_t>(time_recv);
	pong << static_cast<uint8_t>(UDP::PONG);
	NetworkModule::get().sendPacketUDP(pong);
	Net::Packet     pong2(18);
	pong2 << static_cast<uint64_t>(Net::Clock::getMsSinceEpoch());
	pong2 << static_cast<uint8_t>(UDP::PING);
	NetworkModule::get().sendPacketUDP(pong2);
	return 1;
}

int         UdpHandler::pong(Net::Packet &, uint64_t time_recv)
{
	_latency = (Net::Clock::getMsSinceEpoch() - time_recv) / 2;
	return 1;
}

bool		UdpHandler::testPacketId(uint32_t id)
{
	if (_lastPacketId == static_cast<uint32_t>(-1))
		_lastPacketId = id;
	if (id > _lastPacketId)
	{
		uint32_t	val = id - _lastPacketId;
		_lastPacketId = id;
		GameCommand *gc;
		for (; val > 1; --val)
		{
			gc = new GameCommand("retrieve");
			gc->idObject = val + _lastPacketId;
			CommandDispatcher::get().pushCommand(*gc, true);
		}
	   return true;
	}
	return false;
}
