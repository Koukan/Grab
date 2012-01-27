#pragma once
#include <string>
#include <list>
#include "GameState.hpp"

class GSPreload : public GameState
{
public:
	GSPreload();
	~GSPreload();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);
	virtual bool	handleCommand(Command const &command);
};
