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

int		SocketStream::close()
{
	this->shutdown(SHUT_WR);
	return this->Socket::close();
}

int		SocketStream::shutdown(int flags)
{
	return (::shutdown(_handle, flags));
}

int		SocketStream::setNagleEnable(bool flag)
{
	sockopt val = (flag) ? 1 : 0;
	return this->setSockOpt(IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
}

int		SocketStream::getRoundTripTime()
{
#ifndef _WIN32
/*	struct tcp_info info;
	sockopt size = sizeof(info);
	if (getsockopt(_handle, IPPROTO_TCP, TCP_INFO, &info, &size) == -1)
		return -1;
	return info.tcpi_rtt;*/
	return 0;
#else
	return 0;
#endif
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
#include <Mswsock.h>
#pragma comment(lib, "Mswsock.lib")
int     SocketStream::sendfile(std::string const &path)
{
	HANDLE file = ::CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
		return -1;
	BOOL ret = ::TransmitFile(_handle, file, 0, 0, 0, 0, TF_USE_KERNEL_APC);
	CloseHandle(file);
	if (ret == FALSE)
		return -1;
	return 0;
}
#endif

int		SocketStream::sendPackets(std::deque<Packet> &packets, int flags)
{
	if (packets.size() <= 1)
		return this->SocketIO::sendPackets(packets, flags);
	struct iovec	buffers[SocketIO::listSize];

  	size_t	i = 0;
	for (auto &it : packets)
  	{	
		buffers[i].iov_base = const_cast<char*>(it.wr_ptr()); //safe because only read to be sent
		buffers[i].iov_len = it.size() - it.getWindex();
  		++i;
		if (i == SocketIO::listSize)
			break ;
  	}

  	int		res;
#if defined (_WIN32)
  	DWORD		ret = 0;

  	res = ::WSASend(_handle, reinterpret_cast<LPWSABUF>(&buffers), i, &ret, flags, 0, 0);
	if (res <= 0)
		return res;
#else
	struct msghdr	msg;

  	msg.msg_name = 0;
  	msg.msg_namelen = 0;
  	msg.msg_flags = 0;
  	msg.msg_iov = buffers;
  	msg.msg_iovlen = i;
  	msg.msg_control = 0;
  	msg.msg_controllen = 0;
  	int ret = ::sendmsg(_handle, &msg, flags);
	if (ret <= 0)
		return ret;
#endif
	i = 0;
	res = ret;
	std::deque<Packet>::iterator it;
	for (it = packets.begin(); it != packets.end() && res > 0;)
	{
		res -= buffers[i].iov_len;
		if (res >= 0)
		{
			++it;
			packets.pop_front();
		}
		else
		{
			(*it).wr_ptr((*it).getWindex() + (buffers[i].iov_len + res));
			break ;
		}
		++i;
	}
	return ret;
}
