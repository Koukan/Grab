#pragma once

#include <vector>
#include <deque>
#include "../NetDef.hpp"
#include "Thread.hpp"
#include "ConditionVar.hpp"
#include "Task.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Threadpool class
 */
class NET_DLLREQ	ThreadPool
{
  public:
	/*!
		\brief Construct a Threadpool
		\param nbThread Number of initial threads in threadpool
		\details if 0, then the number of the thread is equal to the number of logic processors on the computer
	*/
    ThreadPool(size_t nbThread = 0);
    virtual ~ThreadPool();
	void		pushTask(Net::Task &task);
	void		pushPriorityTask(Net::Task &task);
	/*!
	 \brief Add a task to perform asynchronously 

	 \param task Task to be executed
	 */
	void		pushTask(std::function<void ()> task);
	/*!
	 \brief Add a task to perform asynchronously in the first position

	 \param task Task to be executed with a high priority
	 */
	void		pushPriorityTask(std::function<void ()> task);
	/*!
	 \brief Get the number of waiting tasks

	 \return the number of waiting tasks
	 */
	size_t		size() const;
	/*!
	 \brief	Add dynamically one or more threads to the threadpool 
	 \details No task is lossed
	 \param nb Number of threads to add
	 */
	void		addThread(size_t nb = 1);
	/*!
	 \brief Remove dynamically one or more threads to the threadpool
	 \details No task is lossed
	 \details This function do not wait the thread to terminate
	 \param nb Numbers of thread to remove
	 */
	void		removeThread(size_t nb = 1); // non blocking
	/*!
	 \brief Terminate the threadpool
	 \details All tasks not performed is lossed
	 \details This function blocks until all thread return
	 */
	void		terminate();

  private:
	typedef	::std::vector<Thread*>	threadList;
	typedef	::std::deque<std::function<void ()> >	taskList;

	void				handleTask();

	threadList			_threadsList;
	taskList			_tasksList;
	ConditionVar		_var;
	Mutex				_mutex;
};

NET_END_NAMESPACE
