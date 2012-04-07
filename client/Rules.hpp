#pragma once

#include "GameObject.hpp"

namespace Rules
{
	void		wallTouchObject(Core::GameObject&, Core::GameObject&);
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
	void		setOnline(bool online);
};
