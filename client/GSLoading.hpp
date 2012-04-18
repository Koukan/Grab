#pragma once
#include <string>
#include <list>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "Player.hpp"
#include "Modes.hpp"

class GSInGame;

class GSLoading : public Core::GameState
{
	public:
	GSLoading(std::list<Player *>& players, Modes::Mode mode,
			std::string const &map, unsigned int nbPlayers, bool online);
	virtual ~GSLoading();

	virtual void	onStart();
	virtual bool	handleCommand(Core::Command const &command);

	private:
	template<typename T>
	class Method
	{
	public:
	  T		name;
	  void (GSLoading::*method)(Core::Command const &);
	};

	// handleCommand
	void			goToInGame(Core::Command const &command);
	void			shipSpawn(Core::Command const &command);
	void			setSeed(Core::Command const &command);

	std::list<Player *>			&_players;
	unsigned int				_nbPlayers;
	unsigned int				_nbShip;
	GSInGame				&_game;
	Modes::Mode				_mode;
};
