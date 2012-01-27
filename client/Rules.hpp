#pragma once

#include "GameObject.hpp"

class Rules
{
  public:
	static void		wallTouchObject(GameObject&, GameObject&);
	static void		shotTouchMonster(GameObject&, GameObject&);

  private:
    Rules();
};
