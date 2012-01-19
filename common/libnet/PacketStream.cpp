/*
 * PacketStream.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: snap
 */

#include "PacketStream.hpp"

PacketStream::PacketStream()
{
}

PacketStream::~PacketStream()
{
}

char	*PacketStream::rd_ptr()
{
	return 0;
}

char	*PacketStream::wr_ptr()
{

}

void	PacketStream::rd_ptr(size_t index)
{
	_ss.seekg(index);
	_rindex = index;
}

void	PacketStream::wr_ptr(size_t index)
{
	_ss.seekp(index);
	_windex = index;
}
