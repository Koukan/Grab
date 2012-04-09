#pragma once

#include "GameObject.hpp"

namespace Rules
{
	void		wallTouchObject(Core::GameObject&, Core::GameObject&);
	void		limitWallTouchObject(Core::GameObject&, Core::GameObject&);
	void		shotTouchMonster(Core::GameObject&, Core::GameObject&);
	void		shotTouchPlayer(Core::GameObject&, Core::GameObject&);
	void		deadlyWallsTouchPlayers(Core::GameObject&, Core::GameObject&);
	void		grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2);
	void		grabTouchPlayer(Core::GameObject &o1, Core::GameObject &o2);
	void		grabTouchPlayerOnline(Core::GameObject &o1, Core::GameObject &o2);
	void		grabTouchWall(Core::GameObject &o1, Core::GameObject &o2);
	void		wallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2);
	void		invisibleWallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2);
  	void		playerTouchScore(Core::GameObject& o1, Core::GameObject& o2);
  	void		blackHoleTouchObject(Core::GameObject& o1, Core::GameObject& o2);
	void		playerTouchTrigger(Core::GameObject& o1, Core::GameObject& o2);
	void		blackHoleEndTouchShot(Core::GameObject& blackHole, Core::GameObject& obj);
	void		blackHoleEndTouchMonster(Core::GameObject& blackHole, Core::GameObject& obj);
	void		setOnline(bool online);
};
