#pragma once

#include "GameObject.hpp"

namespace Rules
{
	void		wallTouchObject(Core::GameObject&, Core::GameObject&);
	void		shotTouchMonster(Core::GameObject&, Core::GameObject&);
	void		grabTouchMonster(Core::GameObject& o1, Core::GameObject& o2);
	void		grabTouchPlayer(Core::GameObject &o1, Core::GameObject &o2);
	void		wallsTouchPlayers(Core::GameObject& o1, Core::GameObject& o2);
};
