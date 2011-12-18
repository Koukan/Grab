/*
 * PacketStream.hpp
 *
 *  Created on: Dec 3, 2011
 *      Author: snap
 */

#ifndef PACKETSTREAM_HPP_
#define PACKETSTREAM_HPP_

#include <iostream>
#include <sstream>
#include "Packet.hpp"

class PacketStream : public Packet
{
public:
	PacketStream();
	~PacketStream();

	template <typename T>
	PacketStream& operator<<(T value)
	{
		_ss << value;
		_windex = _ss.tellp();
		_size = _windex;
		return *this;
	}

	template <typename T>
	PacketStream& operator>>(T &value)
	{
		_ss >> value;
		_rindex = _ss.tellg();
		return *this;
	}

	virtual char	*rd_ptr();
	virtual char	*wr_ptr();
	virtual void	rd_ptr(size_t index);
	virtual void	wr_ptr(size_t index);

private:
	std::stringstream	_ss;
};

#endif /* PACKETSTREAM_HPP_ */
