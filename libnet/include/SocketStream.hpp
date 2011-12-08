/*
 * SocketStream.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef SOCKETSTREAM_HPP_
#define SOCKETSTREAM_HPP_

#include "SocketIO.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ SocketStream : public SocketIO
{
public:
	SocketStream();
	~SocketStream();

	int		shutdown(int flags = SHUT_RDWR);

};

NET_END_NAMESPACE

#endif /* SOCKETSTREAM_HPP_ */
