#pragma once

#include <list>
#include <queue>
#include "Module.hpp"
#include "Command.hpp"
#include "CommandHandler.hpp"
#include "Mutex.hpp"

class CommandDispatcher : public Module
{
  public:
    CommandDispatcher();
    virtual ~CommandDispatcher();
	virtual void		init();
	virtual void		update(double elapsedTime = 0);
	virtual void		destroy();
	void				pushCommand(Command &command);
	void				registerHandler(CommandHandler &handler);
	void				removeHandler(CommandHandler &handler);

  private:
	std::list<CommandHandler*>	_handlers;
	std::queue<Command*>		_commands;
	Mutex						_mutex;
};
