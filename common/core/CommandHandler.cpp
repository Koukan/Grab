#include "CommandHandler.hpp"
#include <algorithm>

CORE_USE_NAMESPACE

CommandHandler::CommandHandler()
	: _time(0)
{
}

CommandHandler::~CommandHandler()
{
	Command		const *command;
	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		delete command;
	}
	for (std::list<CommandHandler*>::iterator it = this->_handlers.begin();
		 it != this->_handlers.end(); it++)
		(*it)->removeFather(*this);
	for (std::list<CommandHandler*>::iterator it = this->_fathers.begin();
		 it != this->_fathers.end(); it++)
		(*it)->removeHandler(*this);
}

bool			CommandHandler::handleCommand(Command const &)
{
	return false;
}

bool			CommandHandler::handle(Command const &command)
{
	std::list<CommandHandler*>::const_iterator 	it;
	bool										ret = false;

	ret = this->handleCommand(command);
	if (!ret)
	{
		for (it = this->_handlers.begin(); it != this->_handlers.end(); it++)
		{
			if ((*it)->handle(command))
				return true;
		}
	}
	return ret;
}

void			CommandHandler::handle(double elapsedTime)
{
	Command const								*command;
	std::list<CommandHandler *>::const_iterator it;

	this->_mutex.lock();

	// time command management
	this->_time += static_cast<int>(elapsedTime);
	while (!this->_timeCommands.empty() && this->_timeCommands.top().first < this->_time)
	{
		command = this->_timeCommands.top().second;
		this->_timeCommands.pop();
		this->_mutex.unlock();
		this->handle(*command);
		delete command;
		this->_mutex.lock();
	}
	// end time

	while (!this->_commands.empty())
	{
		command = this->_commands.front();
		this->_commands.pop();
		this->_mutex.unlock();
		this->handle(*command);
		delete command;
		this->_mutex.lock();
	}
	this->_mutex.unlock();
}

void			CommandHandler::pushCommand(Command const &command, bool treatNow)
{
	{
		Net::ScopedLock		lock(this->_mutex);
		this->_commands.push(&command);
	}
	if (treatNow)
		this->handle(0);
}

void			CommandHandler::pushCommand(Command const &command, int time)
{
	this->_timeCommands.push(std::make_pair(this->_time + time, &command));
}

void			CommandHandler::registerHandler(CommandHandler &handler)
{
	this->_handlers.push_back(&handler);
	handler.addFather(*this);
}

void			CommandHandler::addFather(CommandHandler &handler)
{
	this->_fathers.push_back(&handler);
}

void			CommandHandler::removeHandler(CommandHandler &handler)
{
	std::list<CommandHandler*>::iterator	it = std::find(this->_handlers.begin(), this->_handlers.end(), &handler);
	if (it != this->_handlers.end())
		this->_handlers.erase(it);
}

void			CommandHandler::removeHandler()
{
	this->_handlers.clear();
}

void			CommandHandler::removeFather(CommandHandler &handler)
{
	std::list<CommandHandler*>::iterator	it = std::find(this->_fathers.begin(), this->_fathers.end(), &handler);
	if (it != this->_fathers.end())
		this->_fathers.erase(it);
}