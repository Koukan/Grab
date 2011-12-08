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
	int		accept(SocketStream &stream, InetAddr *src = 0, size_t timeout = 0);

private:
	Handle	accept(InetAddr *src = 0);
	int		bind(InetAddr const &addr);
	int 	listen();
};

NET_END_NAMESPACE

#endif /* SOCKETACCEPTOR_HPP_ */
