#pragma once
#include <string>
#include <list>
#include "GameState.hpp"
#include "BulletCommand.hpp"

class GSInGame;

class GSLoading : public GameState
{
public:
	GSLoading(int nbPlayers);
	~GSLoading();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);
	virtual bool	handleCommand(Command const &command);

private:
	struct Method
	{
	  std::string const		name;
	  void (GSLoading::*method)(Command const &);
	};

	void			escape(const InputCommand &event);
	void			buttonClick();
	void			listChoice(std::string const &name);
	void			gameBeginCommand(Command const &);
	void			errorFullGameCommand(Command const &);

	BulletCommand		*_bullet;
	GSInGame			*_ingame;
	int					_nbPlayers;
};
