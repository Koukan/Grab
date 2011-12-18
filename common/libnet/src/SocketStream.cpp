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
