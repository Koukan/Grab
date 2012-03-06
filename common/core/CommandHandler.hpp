#pragma once

#include <list>
#include <queue>
#include "Command.hpp"
#include "Mutex.hpp"

CORE_BEGIN_NAMESPACE

class CORE_DLLREQ CommandHandler
{
  public:
    CommandHandler();
    virtual ~CommandHandler();
	virtual bool		handleCommand(Command const &command);
	bool				handle(Command const &command);
	void				handle(double elapsedTime = 0);
	void				pushCommand(Command const &command, bool treatNow = false);
	void				pushCommand(Command const &command, int time);
	void				registerHandler(CommandHandler &handler);
	void				removeHandler(CommandHandler &handler);
	void				removeHandler();

  private:
	typedef std::priority_queue<std::pair<int, Command const *> >	TimedQueue;

	int							_time;
	std::list<CommandHandler*>	_handlers;
	std::queue<Command const *>	_commands;
	TimedQueue					_timeCommands;
	Net::Mutex					_mutex;
};

CORE_END_NAMESPACE
