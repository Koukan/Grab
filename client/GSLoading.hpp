#pragma once
#include <string>
#include <list>
#include "GameState.hpp"
#include "BulletCommand.hpp"

class GSInGame;

class GSLoading : public Core::GameState
{
public:
	GSLoading(int nbPlayers);
	~GSLoading();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);
  virtual bool	handleCommand(Core::Command const &command);

private:
	struct Method
	{
	  std::string const		name;
	  void (GSLoading::*method)(Core::Command const &);
	};

  void			escape(const Core::InputCommand &event);
	void			buttonClick();
	void			listChoice(std::string const &name);
  void			gameBeginCommand(Core::Command const &);
  void			errorFullGameCommand(Core::Command const &);

  Core::BulletCommand		*_bullet;
	GSInGame			*_ingame;
	int					_nbPlayers;
};
