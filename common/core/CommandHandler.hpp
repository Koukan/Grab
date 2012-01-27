#pragma once

#include <list>
#include <queue>
#include "Command.hpp"
#include "Mutex.hpp"

class CommandHandler
{
  public:
    CommandHandler();
    virtual ~CommandHandler();
	virtual bool		handleCommand(Command const &command);
	bool				handle(Command const &command);
	void				handle(double elapsedTime = 0);
	void				pushCommand(Command const &command, bool treatNow = false);
	void				registerHandler(CommandHandler &handler);
	void				removeHandler(CommandHandler &handler);
	void				removeHandler();

  private:
	std::list<CommandHandler*>	_handlers;
	std::queue<Command const *>	_commands;
	Net::Mutex					_mutex;
};
