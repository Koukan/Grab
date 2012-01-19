/*
 * SocketConnector.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef SOCKETCONNECTOR_HPP_
#define SOCKETCONNECTOR_HPP_

#include "SocketStream.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ SocketConnector : public Socket
{
public:
	SocketConnector();
	~SocketConnector();

	int		setup(InetAddr const &addr, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	int		connect(SocketStream &stream, InetAddr const &addr, size_t timeout = 0);

private:
};

NET_END_NAMESPACE

#endif /* HandleCONNECTOR_HPP_ */
