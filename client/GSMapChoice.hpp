#pragma once

#include "GameState.hpp"
#include "Modes.hpp"

class GSMapChoice : public Core::GameState
{
public:
	GSMapChoice(Modes::Mode mode);
	~GSMapChoice();

	virtual void		onStart();
	virtual void		back();
	void				mapChoice(Core::GUIElement &elem);
	void				createParty();

private:
	Modes::Mode							_mode;
	std::string							_map;
	std::map<std::string, std::string>	_maps;
};

