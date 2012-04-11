#include <cstdlib>
#include "CommandDispatcher.hpp"
#include "GameState.hpp"

CORE_USE_NAMESPACE

CommandDispatcher::CommandDispatcher()
	: Module("CommandDispatcher", 5), _update(true)
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
	if (_update)
		this->handle(elapsedTime);
}

void			CommandDispatcher::destroy()
{
}

void			CommandDispatcher::start()
{
	_update = true;
}

void			CommandDispatcher::stop()
{
	_update = false;
}