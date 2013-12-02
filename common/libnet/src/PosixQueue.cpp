#if defined (__unix__)
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "PosixQueue.hpp"

NET_USE_NAMESPACE

PosixQueue::PosixQueue(std::string const &name, int flags)
{
	if (flags == 0)
		flags = O_RDWR | O_NONBLOCK | O_CREAT;
	_handle = ::mq_open(name.c_str(), flags, 0666, nullptr);
	if (_handle == -1)
		printLastError();
}

int		PosixQueue::send(const char *buff, size_t size, int flags)
{
	return ::mq_send(_handle, buff, size, flags);
}

int		PosixQueue::recv(char *buff, size_t size, int flags)
{
	unsigned int prio;
	return ::mq_receive(_handle, buff, size, &prio);	
}
#endif
