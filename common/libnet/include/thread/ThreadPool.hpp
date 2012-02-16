#pragma once

#include <list>
#include <queue>
#include "ConditionVar.hpp"
#include "Thread.hpp"
#include "Task.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ	ThreadPool
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
	ConditionVar		_condvar;
};

NET_END_NAMESPACE
