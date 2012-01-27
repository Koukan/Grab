#pragma once

#include <list>
#include <queue>
#include "Task.hpp"
#include "Net.hpp"

class ThreadPool
{
  public:
    ThreadPool();
    virtual ~ThreadPool();
	bool			init(size_t nbThread);
	void		pushTask(Task &task);

  private:
	typedef	std::list<Net::Thread*>	threadList;
	typedef	std::queue<Task*>		taskList;

	void				handleTask();

	threadList			_threadsList;
	taskList			_tasksList;
	Net::ConditionVar	_condvar;
};
