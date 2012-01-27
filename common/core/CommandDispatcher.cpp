#include <cstdlib>
#include "CommandDispatcher.hpp"
#include "GameState.hpp"

CommandDispatcher::CommandDispatcher() : Module("CommandDispatcher", 5)
{
}

CommandDispatcher::~CommandDispatcher()
{
}

void			CommandDispatcher::init()
{
}

void			CommandDispatcher::update(double elapsedTime)
{
	this->handle(elapsedTime);
}

void			CommandDispatcher::destroy()
{
}
