#pragma once

#include "GameState.hpp"
#include "Modes.hpp"
#include "Player.hpp"

class GUIPlayerButton;

class GSBindPlayer : public Core::GameState
{
public:
	GSBindPlayer(Modes::Mode mode, std::string const &map, unsigned int nbPlayers, bool online);
	~GSBindPlayer();

	virtual void	onStart();
	virtual void	onResume();
	virtual bool	handleCommand(Core::Command const &command);
	void			goToInGame();
	void			addDemand(Core::GUICommand::PlayerType type);
	void			removePlayer(uint32_t nb, Core::GUICommand::PlayerType type);
	void			updatePlayer(uint32_t nb, uint32_t ship, bool ready);
	bool			isOnline() const;
	void			addSelected(GUIPlayerButton*, Core::GUICommand::PlayerType);
	void			removeSelected(Core::GUICommand::PlayerType);
	GUIPlayerButton	*selectedBy(Core::GUICommand::PlayerType) const;
	void			changeMap(std::string const &map);
	virtual void	back(Core::InputCommand const &cmd);

private:
	void			answerBind(Core::Command const &command);
	void			removePlayer(Core::Command const &command);
	void			updatePlayer(Core::Command const &command);
	void			goToLoadGame(Core::Command const &command);
	void			mapChoice(std::string const &map);
	void			mapChoice(Core::Command const &command);
	void			shipSpawn(Core::Command const &command);

	typedef std::map<uint32_t, Core::GUICommand::PlayerType> DemandMap;
	struct	Method
	{
		std::string const	name;
		void	(GSBindPlayer::*func)(Core::Command const &);
	};

	Modes::Mode					_mode;
	std::string					_map;
	unsigned int				_nbPlayers;
	bool						_online;
	Player						*_players[4];
	int							_nbReady;
	int							_nbPending;
	uint32_t					_id;
	bool						_gameBegin;
	DemandMap					_demands;
	std::list<GUIPlayerButton*>	_buttons;
	std::map<Core::GUICommand::PlayerType, GUIPlayerButton*>	_binds;
	Core::CoreFont				*_mapFont;
};
