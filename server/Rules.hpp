#pragma once

#include "GameObject.hpp"

class Rules
{
  public:
	static void		wallTouchObject(Core::GameObject&, Core::GameObject&);
	static void		shotTouchMonster(Core::GameObject&, Core::GameObject&);
	static void		shotTouchClient(Core::GameObject&, Core::GameObject&);
  	static void		blackHoleTouchObject(Core::GameObject& o1, Core::GameObject& o2);
	static void		blackHoleEndTouchShot(Core::GameObject& blackHole, Core::GameObject& obj);
	static void		blackHoleEndTouchMonster(Core::GameObject& blackHole, Core::GameObject& obj);

  private:
    Rules();
};
