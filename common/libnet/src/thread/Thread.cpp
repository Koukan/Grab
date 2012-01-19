#include "Thread.hpp"

NET_USE_NAMESPACE

Thread::Thread(IThreadSubscriber &func) :
	   	_func(&func), _state(false)
{}

Thread::~Thread()
{
  if (_state)
	this->cancel();
  delete _func;
}

void       Thread::run()
{
  _func->call();
}
