#pragma once
#include <map>
#include <vector>
#include "GameState.hpp"
#include "BulletCommand.hpp"
#include "GameCommand.hpp"
#include "PhysicObject.hpp"
#include "Font.hpp"
#include "Resources.hpp"

class GSInGame : public GameState
{
public:
	GSInGame(int nbPlayers);
	~GSInGame();
	virtual void	onStart();
	virtual void	onEnd();
	virtual void	update(double elapsedTime = 0);
	virtual bool	handleCommand(Command const &command);
	void			preload();

private:
	template<typename T>
	class Method
	{
	public:
	  T		name;
	  void (GSInGame::*method)(GameCommand const &);
	};

	void		inputEscape(InputCommand const &event);
	void		inputSpace(InputCommand const &event);
	void		inputUp(InputCommand const &event);
 	void		inputDown(InputCommand const &event);
  	void		inputLeft(InputCommand const &event);
  	void		inputRight(InputCommand const &event);
	void		releaseInputUpDown(InputCommand const &event);
  	void		releaseInputLeftRight(InputCommand const &event);
	void		releaseInputSpace(InputCommand const &/*event*/);

	// HandleCommand

	void		destroy(GameCommand const &event);
	void		spawn(GameCommand const &event);
	void		score(GameCommand const &event);
	void		life(GameCommand const &event);
	void		move(GameCommand const &event);
	void		rangeid(GameCommand const &event);

	void		retrieve(uint32_t idPacket);

  	void		throwShip();

	void		updatePositions(GameCommand const &event, PhysicObject &obj) const;
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
	std::vector<Font*>    _scoreFonts;
	std::vector<Font*>    _nameFonts;
	PhysicObject	*_ship;
	uint32_t	_rangeBegin;
	uint32_t	_rangeEnd;
	uint32_t	_currentId;
	bool		_fire;
	double		_elapsedTime;
};
