#pragma once
#include <string>
#include <list>
#include "GameState.hpp"

class GSPreload : public Core::GameState
{
public:
	GSPreload();
	~GSPreload();
	virtual void	onStart();
	virtual void	onPause();
	virtual void	onPlay();
	virtual	void	update(double elapseTime = 0);
  virtual bool	handleCommand(Core::Command const &command);

private:
 	Core::Sound		*_sound;
};
