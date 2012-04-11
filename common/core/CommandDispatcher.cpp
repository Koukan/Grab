#include <cstdlib>
#include "CommandDispatcher.hpp"
#include "GameState.hpp"

CORE_USE_NAMESPACE

CommandDispatcher::CommandDispatcher()
	: Module("CommandDispatcher", 5)
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