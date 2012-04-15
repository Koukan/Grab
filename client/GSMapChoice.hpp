#pragma once

#include "GameState.hpp"
#include "Modes.hpp"
#include "GSBindPlayer.hpp"

class GSMapChoice : public Core::GameState
{
public:
	GSMapChoice(Modes::Mode mode, int nbPlayers, bool online);
	~GSMapChoice();

	virtual void		onStart();
	virtual void		back();
	void				mapChoice(Core::GUIElement &elem);
	void				createParty();

private:
	Modes::Mode							_mode;
	int									_nbPlayers;
	bool								_online;
	GSBindPlayer						*_bindPlayer;
	std::string							_map;
	std::map<std::string, std::string>	_maps;
};

