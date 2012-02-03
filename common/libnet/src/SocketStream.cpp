/*
 * SocketStream.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "SocketStream.hpp"

NET_USE_NAMESPACE

SocketStream::SocketStream()
{
}

SocketStream::~SocketStream()
{
}

int		SocketStream::shutdown(int flags)
{
  return (::shutdown(_handle, flags));
}

#if defined (__linux__)
#include <sys/sendfile.h>
#include <fcntl.h>
int		SocketStream::sendfile(std::string const &path)
{
	int		file = ::open(path.c_str(), O_RDONLY);
	if (file == -1)
		return -1;
	int		ret = ::sendfile(_handle, file, 0, (size_t)-1);
	::close(file);
	return ret;
}
#elif defined (__FreeBSD__)
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <fcntl.h>
int     SocketStream::sendfile(std::string const &path)
{
	int     file = ::open(path.c_str(), O_RDONLY);
	if (file == -1)
		return -1;
	off_t	sent;
	int     ret = ::sendfile(file, _handle, 0, 0, 0, &sent, 0);
	::close(file);
	if (ret == -1)
		return -1;
	return sent;
}
#elif defined (_WIN32)
int     SocketStream::sendfile(std::string const &path)
{
	Handle file = ::CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
		return -1;
	BOOL ret = ::TransmitFile(_handle, file, 0, 0, 0, 0, TF_USE_KERNEL_APC);
	CloseHandle(file);
	if (ret == FALSE)
		return -1;
	return 0;
}
#endif
