#include <iostream>
#include "Server.hpp"
#include "Game.hpp"
#include "PacketType.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameListCommand.hpp"
#include "Command.hpp"

Server::Server() : Net::SizeHeaderPacketHandler<>(4096),
		_name(""), _game(0)
{
	NetworkModule::get().setServer(this);
}

Server::~Server()
{
	NetworkModule::get().setServer(0);
}

int			Server::handleInputPacket(Net::Packet &packet)
{
	static bool			(Server::* const methods[])(Net::Packet &) = {
			NULL,
			&Server::treatEtablishedPacket,
			NULL,
			&Server::treatGamePacket,
			&Server::treatEndListGamePacket,
			NULL,
			&Server::treatPlayerPacket,
			NULL, // CREATE_GAME
			NULL, // RESOURCE
			NULL, // REQUIRE_RESOURCE
			NULL, // RESOURCE_PART
			NULL, // END_RESOURCE
			NULL, // END_RESOURCES
			&Server::treatGameStatePacket,
			&Server::treatErrorPacket,
			&Server::rangeId
	};
	uint8_t			type;

	packet >> type;
	std::cout << "incomming packet " << int(type) << std::endl;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		return (this->*methods[type])(packet);
	}
	return false;
}

void		Server::setGame(Game &game)
{
	this->_game = &game;
}

// Generer command comme gamecommand et la push dans commandDispatcher

bool		Server::treatEtablishedPacket(Net::Packet &)
{
	return true;
}

bool		Server::treatGamePacket(Net::Packet &packet)
{
	uint16_t	idGame;
	uint8_t		nbPlayers;
	uint8_t		state;

	packet >> idGame;
	packet >> nbPlayers;
	packet >> state;
	CommandDispatcher::get().pushCommand(*(new GameListCommand("listGame", idGame, nbPlayers, state)));
	return true;
}

bool		Server::treatEndListGamePacket(Net::Packet &)
{
	CommandDispatcher::get().pushCommand(*(new GameListCommand("listGame", 0, 0, 0)));
	return true;
}

bool		Server::treatPlayerPacket(Net::Packet &packet)
{
	uint16_t	status;
	std::string name;
	uint8_t		idPlayer;

	packet >> status;
	packet >> idPlayer;

	return true;
}

bool		Server::treatGameStatePacket(Net::Packet &packet)
{
	uint8_t err;

	packet >> err;
	if (err == GameStateEnum::BEGIN)
	{
		CommandDispatcher::get().pushCommand(*(new Command("GameBegin")));
	}
	else
	{
		GameStateManager::get().popState();
	}
	return true;
}

bool		Server::treatErrorPacket(Net::Packet &packet)
{
	static const char* errorTexts[] =
	{
		"Login already used",
		"Game already full",
		"Selected game doesn't exist anymore",
		"This server can't accept another game"
	};
	uint16_t err;
	std::string errText;

	packet >> err;
	if (err < sizeof(errorTexts) / sizeof(*errorTexts))
		errText = errorTexts[err];
	else
		errText = "Unknown error";
#if defined (_WIN32) 
	MessageBox(NULL, errorTexts[err], TEXT("Error"), MB_OK);
#endif
	std::cerr << errorTexts[err] << std::endl;
	CommandDispatcher::get().pushCommand(*(new Command("ErrorFullGame")));
	return true;
}

bool		Server::rangeId(Net::Packet &packet)
{
	uint32_t	begin;
	uint32_t	end;
	uint8_t		idPlayer;

	packet >> idPlayer;
	packet >> begin;
	packet >> end;
	CommandDispatcher::get().pushCommand(*(new GameCommand("rangeid", begin, end, idPlayer)));
	return true;
}
