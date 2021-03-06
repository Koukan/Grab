/*
 * SocketAcceptor.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef SOCKETACCEPTOR_HPP_
#define SOCKETACCEPTOR_HPP_

#include "Socket.hpp"
#include "SocketStream.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ SocketAcceptor : public Socket
{
public:
	SocketAcceptor();
	~SocketAcceptor();

	int		setup(InetAddr const &addr, bool reuseAddr = true,  int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	int		accept(SocketStream &stream, InetAddr *src = 0, bool nonblocking = false, size_t timeout = 0);
	void	setBacklog(int backlog);

private:
	Handle	accept(InetAddr *src, bool nonblocking);
	int		bind(InetAddr const &addr);
	int 	listen();

	int		_backlog;
};

NET_END_NAMESPACE

#endif /* SOCKETACCEPTOR_HPP_ */
