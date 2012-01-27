#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

bool			ThreadPool::init(size_t nbThread)
{
	Net::Thread		*thread;

	for (; nbThread > 0; nbThread--)
	{
		thread = new Net::Thread(this, &ThreadPool::handleTask);
		_threadsList.push_back(thread);
		if (!thread->start())
			return false;
	}
	return true;
}

void		ThreadPool::pushTask(Task &task)
{
	this->_condvar.lock();
	this->_tasksList.push(&task);
	this->_condvar.signal();
	this->_condvar.unlock();
}

void		ThreadPool::handleTask()
{
	Task	*task;

	while (true)
	{
		this->_condvar.lock();
		if (this->_tasksList.empty())
		{
			this->_condvar.wait();
			this->_condvar.unlock();
		}
		else
		{
			task = this->_tasksList.front();
			this->_tasksList.pop();
			this->_condvar.unlock();
			(*task)();
			delete task;
		}
	}
}
