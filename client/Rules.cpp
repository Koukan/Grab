#include "Rules.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

void	Rules::wallTouchObject(Core::GameObject &, Core::GameObject &o2)
{
	o2.erase();
}

void		Rules::shotTouchMonster(Core::GameObject &o1, Core::GameObject &)
{
	o1.erase();
}
