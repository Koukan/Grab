#pragma once

#include "GameObject.hpp"

class Rules
{
	public:
	static void		wallTouchObject(Core::GameObject&, Core::GameObject&);
	static void		limitWallTouchObject(Core::GameObject&, Core::GameObject&);
	static void		shotTouchMonster(Core::GameObject&, Core::GameObject&);
	static void		shotTouchPlayer(Core::GameObject&, Core::GameObject&);
	static void		deadlyWallsTouchPlayers(Core::GameObject&, Core::GameObject&);
	static void		grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2);
	static void		grabTouchPlayer(Core::GameObject &o1, Core::GameObject &o2);
	static void		grabTouchPlayerOnline(Core::GameObject &o1, Core::GameObject &o2);
	static void		grabTouchWall(Core::GameObject &o1, Core::GameObject &o2);
	static void		wallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2);
	static void		invisibleWallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2);
  	static void		playerTouchScore(Core::GameObject& o1, Core::GameObject& o2);
  	static void		blackHoleTouchObject(Core::GameObject& o1, Core::GameObject& o2);
	static void		playerTouchTrigger(Core::GameObject& o1, Core::GameObject& o2);
	static void		blackHoleEndTouchShot(Core::GameObject& blackHole, Core::GameObject& obj);
	static void		blackHoleEndTouchMonster(Core::GameObject& blackHole, Core::GameObject& obj);
	static void		setOnline(bool online);

	private:
	Rules();
};
