#pragma once
#include <map>
#include <vector>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "GameCommand.hpp"
#include "PhysicObject.hpp"
#include "Font.hpp"
#include "Resources.hpp"
#include "Ship.hpp"

class GSInGame : public Core::GameState
{
public:
	GSInGame(int nbPlayers);
	~GSInGame();
	virtual void	onStart();
	virtual void	onEnd();
	virtual void	update(double elapsedTime = 0);
  virtual bool	handleCommand(Core::Command const &command);
	void			preload();

private:
	template<typename T>
	class Method
	{
	public:
	  T		name;
	  void (GSInGame::*method)(GameCommand const &);
	};

	void		inputEscape(Core::InputCommand const &event);
	void		inputSpace(Core::InputCommand const &event);
	void		inputUp(Core::InputCommand const &event);
 	void		inputDown(Core::InputCommand const &event);
  	void		inputLeft(Core::InputCommand const &event);
  	void		inputRight(Core::InputCommand const &event);
	void		releaseInputUpDown(Core::InputCommand const &event);
  	void		releaseInputLeftRight(Core::InputCommand const &event);
	void		releaseInputSpace(Core::InputCommand const &/*event*/);

	// HandleCommand

	void		destroy(GameCommand const &event);
	void		spawn(GameCommand const &event);
	void		score(GameCommand const &event);
	void		life(GameCommand const &event);
	void		move(GameCommand const &event);
	void		rangeid(GameCommand const &event);

	void		retrieve(uint32_t idPacket);

  	void		throwShip();

  void		updatePositions(GameCommand const &event, Core::PhysicObject &obj) const;
	void		displayScores();

	void		loadP1(GameCommand const &event);
	void		loadP2(GameCommand const &event);
	void		loadP3(GameCommand const &event);
	void		loadP4(GameCommand const &event);
	void		loadMonster(GameCommand const &event);
	void		loadShoot(GameCommand const &event);
	
	uint32_t	getNextId();

	uint16_t	_idPlayer;
	int		_nbPlayers;
	std::vector<uint32_t> _scores;
  std::vector<Core::CoreFont*>    _scoreFonts;
  std::vector<Core::CoreFont*>    _nameFonts;
  Core::PhysicObject	*_ship;
	uint32_t	_rangeBegin;
	uint32_t	_rangeEnd;
	uint32_t	_currentId;
	bool		_fire;
	double		_elapsedTime;
};
