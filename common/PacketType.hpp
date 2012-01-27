#pragma once

namespace UDP
{
	enum	Type
	{
		SPAWN = 0,
		DESTROY = 1,
		MOVE = 2,
		SCORE = 3,
		STATEMENT = 4,
		RETRIEVE = 5,
		PING = 6,
		PONG = 7
	};
}

namespace TCP
{
	enum	Type
	{
		CONNECTION = 0,
		ETABLISHED = 1,
		LIST_GAMES = 2,
		GAME = 3,
		END_LIST_GAME = 4,
		CONNECT_GAME = 5,
		PLAYER = 6,
		CREATE_GAME = 7,
		RESOURCE = 8,
		REQUIRE_RESOURCE = 9,
		RESOURCE_PART = 10,
		END_RESOURCE = 11,
		END_RESOURCES = 12,
		GAMESTATE = 13,
		TCP_ERROR = 14, // may be Error, but WinGDI.h already defines it on Windows
		RANGEID = 15
	};
}

namespace	Error
{
	enum	Type
	{
		LOGIN = 0,
		GAME_FULL = 1,
		GAME_NOT_EXIST = 2,
		SERVER_FULL  = 3
	};
}

namespace	GameStateEnum
{
	enum	Type
	{
		BEGIN = 0,
		END = 1
	};
}

namespace	PlayerStatus
{
	enum	Type
	{
		CONNECTED = 0,
		READY = 1,
		DISCONNECTED = 2
	};
}
