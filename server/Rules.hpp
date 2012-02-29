#pragma once

#include "GameObject.hpp"

class Rules
{
  public:
	static void		wallTouchObject(Core::GameObject&, Core::GameObject&);
	static void		shotTouchMonster(Core::GameObject&, Core::GameObject&);
	static void		shotTouchClient(Core::GameObject&, Core::GameObject&);

  private:
    Rules();
};
