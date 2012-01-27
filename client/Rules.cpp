#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

#include <iostream>
void	Rules::wallTouchObject(GameObject &, GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(GameObject&o1, GameObject&o2)
{
	o1.erase();	
}
