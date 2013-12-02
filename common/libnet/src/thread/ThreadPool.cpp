#include <unordered_map>
#include "ThreadPool.hpp"

NET_USE_NAMESPACE

#if defined(_WIN32)
# define TLS __declspec(thread)
#else
# define TLS __thread
#endif

static TLS bool _continue = true;

ThreadPool::ThreadPool(size_t nbThread)
{
	if (nbThread == 0)
	{
		nbThread = Net::Thread::hardware_concurrency();
		if (nbThread > 1)
			nbThread--;
	}
	this->addThread(nbThread);
}	

ThreadPool::~ThreadPool()
{
	this->terminate();
}

void		ThreadPool::pushTask(Net::Task &task)
{
	this->pushTask([&] {task(); delete &task;});
}

void		ThreadPool::pushPriorityTask(Net::Task &task)
{
	this->pushPriorityTask([&] {task(); delete &task;});
}

void		ThreadPool::pushTask(std::function<void ()> task)
{
	Net::LockGuard		lock(_mutex);
	this->_tasksList.emplace_back(task);
	this->_var.notify_one();
}

void		ThreadPool::pushPriorityTask(std::function<void ()> task)
{
	Net::LockGuard		lock(_mutex);
	this->_tasksList.emplace_front(task);
	this->_var.notify_one();
}


size_t		ThreadPool::size() const
{
	return this->_tasksList.size();
}

void		ThreadPool::addThread(size_t nb)
{
	for (; nb > 0; nb--)
		_threadsList.push_back(new Net::Thread([this] { handleTask();}));
}

void		ThreadPool::removeThread(size_t nb)
{
	nb = (nb < _threadsList.size()) ? nb : _threadsList.size();
	for (size_t i = 0; i < nb; ++i)
		this->pushPriorityTask([&] {_continue = false;});
}

void		ThreadPool::terminate()
{
	_mutex.lock();
	_tasksList.clear();
	_mutex.unlock();
	this->removeThread(_threadsList.size());
	for (auto it = this->_threadsList.begin(); it != this->_threadsList.end(); ++it)
		(*it)->join();
	this->_threadsList.clear();
	_tasksList.clear(); // now safe since all threads joined
}

void		ThreadPool::handleTask()
{
	while (_continue)
	{
		Net::UniqueLock lock(_mutex);
		this->_var.wait(lock, [this]{return !this->_tasksList.empty();});
		auto task = this->_tasksList.front();
		this->_tasksList.pop_front();
		lock.unlock();
		task();
	}
}
