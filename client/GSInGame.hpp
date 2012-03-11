#pragma once
#include <map>
#include <vector>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "GameCommand.hpp"
#include "PhysicObject.hpp"
#include "Font.hpp"
#include "Resources.hpp"
#include "Player.hpp"
#include "Ship.hpp"
#include "Modes.hpp"
#include <list>

class GSInGame : public Core::GameState
{
public:
	GSInGame(std::list<Player *> const &players, Modes::Mode mode,
			 std::string const &map, unsigned int nbPlayers, bool online);
	virtual ~GSInGame();
	virtual void	onStart();
	virtual void	onEnd();
	virtual bool	handleCommand(Core::Command const &command);
	void			preload();
	void			playerDie(Player &player);

private:
	template<typename T>
	class Method
	{
		public:
			T		name;
			void (GSInGame::*method)(GameCommand const &);
	};

	void		gameover();
	void		inputEscape(Core::InputCommand const &event);
	void		registerShipCallbacks();

	// HandleCommand

	void		score(GameCommand const &event);
	void		move(GameCommand const &event);
	void		rangeid(GameCommand const &event);
	void		spawnspawner(GameCommand const &event);
	void		spawndecoration(GameCommand const &event);
	void		spawnsound(GameCommand const &event);
	void		spawnend(GameCommand const &event);
	void		respawnplayer(GameCommand const &event);
	void		setSeed(GameCommand const &event);

	void		retrieve(uint32_t idPacket);
	void		updatePositions(GameCommand const &event, Core::PhysicObject &obj) const;
	void		displayScores();

  	void		loadShoot(GameCommand const &event);

	uint32_t	getNextId();

	void		createShips();

	uint16_t						_idPlayer;
	std::list<Player *> const		&_players;
	Modes::Mode						_mode;
	std::string const				_map;
	unsigned int					_nbPlayers;
	unsigned int					_nbDie;
	bool							_online;
	std::vector<uint32_t>			_scores;
	std::vector<Core::CoreFont*>    _scoreFonts;
	std::vector<Core::CoreFont*>    _nameFonts;
	uint32_t						_rangeBegin;
	uint32_t						_rangeEnd;
	uint32_t						_currentId;
	bool							_fire;
	double							_elapsedTime;
	Net::MTRand						_rand;
};
