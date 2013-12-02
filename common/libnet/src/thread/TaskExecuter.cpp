#include "TaskExecuter.hpp"
#include "Clock.hpp"

NET_USE_NAMESPACE

TaskExecuter::TaskExecuter()
{
}

TaskExecuter::~TaskExecuter()
{
}

std::size_t			TaskExecuter::pushReturnTask(std::function<void ()> func)
{
	LockGuard		lock(_mutex);
	_tasks.emplace_back(func);
	return _tasks.size();
}

void				TaskExecuter::execute()
{

	_mutex.lock();
	std::deque<std::function<void ()>>		funcs(std::move(_tasks));
	_mutex.unlock();
	for (auto &f : funcs)
		f();
}

void				TaskExecuter::executeOneTask()
{
	_mutex.lock();
	auto	task = _tasks.front();
	_tasks.pop_front();
	_mutex.unlock();
	task();
}

void				TaskExecuter::execute(size_t time)
{
	size_t									i = 0;
	Net::Clock								clock;

	do 
	{
		_mutex.lock();
		auto size = (_tasks.size() < 10) ? _tasks.size() : 10;
		std::deque<std::function<void ()>>	funcs;
		for (i = 0; i < size; i++)
			funcs.emplace_back(_tasks[i]);
		_tasks.erase(_tasks.begin(), _tasks.begin() + i);
		_mutex.unlock();

		if (funcs.empty())
			return ;
		for (auto &f : funcs)
			f();
	} while (clock.getElapsedTime() < time);
}

bool				TaskExecuter::empty() const
{
	return _tasks.empty();
}

unsigned int		TaskExecuter::size() const
{
	return _tasks.size();
}
