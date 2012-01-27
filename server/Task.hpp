#pragma once

class Task
{
  public:
    Task(){}
    virtual ~Task(){}
	virtual void	operator()() = 0;
};
