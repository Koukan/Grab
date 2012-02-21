#pragma once

#include "GameState.hpp"
#include "Modes.hpp"
#include "Player.hpp"


class GSBindPlayer : public Core::GameState
{
public:
	GSBindPlayer(Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online);
	~GSBindPlayer();

	void onStart();
	void goToShipSelection();

private:
	Modes::Mode _mode;
	std::string const _map;
	unsigned int _nbPlayers;
	bool _online;
//	std::list<Core::Player *> _players;
	Player *_players[4];
	int _nbReady;
	int _nbPending;
};
