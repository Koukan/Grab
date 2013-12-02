#pragma once
#if defined (__unix__) && !defined(__APPLE__)
#include "SocketIO.hpp"
NET_BEGIN_NAMESPACE

class NET_DLLREQ PosixQueue : public SocketIO
{
public:
	PosixQueue(std::string const &name, int flags = 0);

	//flags is used as priority here
	int	send(const char *buff, size_t size, int flags = 0) override;
	int	recv(char *buff, size_t size, int flags = 0) override;
};

NET_END_NAMESPACE
#endif
