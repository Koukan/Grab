/*
 * SocketStream.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#include "SocketStream.hpp"

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
