#pragma once

#include "GameState.hpp"
#include "Modes.hpp"
#include "Player.hpp"


class GSBindPlayer : public Core::GameState
{
public:
	GSBindPlayer(Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online);
	~GSBindPlayer();

	void			onStart();
	void			goToInGame();
	void			addDemand(Core::GUICommand::PlayerType type);

	bool			isOnline() const;

private:
	struct Demand
	{
		Demand(int id, Core::GUICommand::PlayerType type)
			: id(id), type(type)
		{}

		int								id;
		Core::GUICommand::PlayerType	type;
	};

	Modes::Mode			_mode;
	std::string const	_map;
	unsigned int		_nbPlayers;
	bool				_online;
	Player				*_players[4];
	int					_nbReady;
	int					_nbPending;
	int					_id;
	std::list<Demand>	_demands;
};
