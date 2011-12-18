#pragma once

class CommandHandler
{
  public:
    CommandHandler(){}
    virtual ~CommandHandler(){}
	virtual bool		handleCommand(Command &command) = 0;
};
