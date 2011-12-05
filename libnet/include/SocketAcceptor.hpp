/*
 * SocketAcceptor.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef HandleACCEPTOR_HPP_
#define HandleACCEPTOR_HPP_

#include "Socket.hpp"
#include "SocketStream.hpp"

class SocketAcceptor : public Socket
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

#endif /* HandleACCEPTOR_HPP_ */
