#pragma once
#include <string>
#include <list>
#include "GameState.hpp"

class GSSplashScreen : public Core::GameState
{
public:
	GSSplashScreen();
	~GSSplashScreen();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);

private:
	bool		_update;
};
