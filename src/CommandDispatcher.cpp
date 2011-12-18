#include "CommandDispatcher.hpp"

CommandDispatcher::CommandDispatcher() : Module("CommandDispatcher")
{
}

CommandDispatcher::~CommandDispatcher()
{
	Command		*command;
	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		delete command;
	}
}

void			CommandDispatcher::init()
{
}

void			CommandDispatcher::update(double elapsedTime)
{
	Command										*command;
	std::list<CommandHandler*>::const_iterator 	it;

	this->_mutex.lock();
	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		//this->_mutex.unlock();
		for (it = this->_handlers.begin(); it != this->_handlers.end(); it++)
		{
			(*it)->handleCommand(*command);
		}
		delete command;
		//this->_mutex.lock();
	}
	this->_mutex.unlock();
}

void			CommandDispatcher::destroy()
{
}

void			CommandDispatcher::pushCommand(Command &command)
{
	ScopedLock		lock(this->_mutex);

	this->_commands.push(&command);
}

void			CommandDispatcher::registerHandler(CommandHandler &handler)
{
	this->_handlers.push_back(&handler);
}

void			CommandDispatcher::removeHandler(CommandHandler &handler)
{
	std::list<CommandHandler*>::iterator	it2;

	for (std::list<CommandHandler*>::iterator it = this->_handlers.begin();
		 it != this->_handlers.end();)
	{
		it2 = it++;
		if (*it2 == &handler)
			this->_handlers.erase(it2);
	}
}
