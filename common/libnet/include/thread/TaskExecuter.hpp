#pragma once

#include <queue>
#include "NetDef.hpp"
#include "Mutex.hpp"
#include "Task.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ TaskExecuter
{
public:
	TaskExecuter();
	virtual ~TaskExecuter();
	std::size_t			pushReturnTask(std::function<void ()> func);
	void				execute();
	void				executeOneTask();
	void				execute(size_t nb);
	bool				empty() const;
	unsigned int		size() const;
	
private:
	std::deque<std::function<void ()>>	_tasks;
	Mutex								_mutex;
};

NET_END_NAMESPACE
