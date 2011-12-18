/*
 * Packet.hpp
 *
 *  Created on: Nov 20, 2011
 *      Author: snap
 */

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include "NetDef.hpp"
#include "InetAddr.hpp"
#include "DataBlock.hpp"

NET_BEGIN_NAMESPACE

class NET_DLLREQ Packet
{
public:
	Packet(size_t size);
	Packet(DataBlock &data, size_t size = 0);
	Packet(Packet const &other);
	virtual ~Packet();

	Packet	*clone();
	Packet	*duplicate() const;
	void	release();
	size_t	size() const;
	size_t	capacity() const;
	virtual char	*rd_ptr();
	virtual char	*wr_ptr();
	virtual void	rd_ptr(size_t index);
	virtual void	wr_ptr(size_t index);
	DataBlock	*getDataBlock() const;
	char	*base() const;
	void	reset();
	size_t	getRindex() const;
	size_t	getWindex() const;
	bool	isConsumned() const;
	bool	isFull()	const;
	InetAddr	&getAddr();
	void	setSize(size_t size);
	void	setDestination(InetAddr const &addr);

	void	addBuffer(char *src, size_t size);

	Packet& operator<<(bool value);
	Packet&	operator<<(char value);
    Packet& operator<<(int8_t value);
    Packet& operator<<(uint8_t value);
    Packet& operator<<(int16_t value);
    Packet& operator<<(uint16_t value);
    Packet& operator<<(int32_t value);
    Packet& operator<<(uint32_t value);
    Packet& operator<<(int64_t value);
    Packet& operator<<(uint64_t value);
    Packet& operator<<(std::string const &str);
	Packet& operator<<(char const *str);

	Packet& operator>>(bool &value);
	Packet& operator>>(char &value);
    Packet& operator>>(int8_t &value);
    Packet& operator>>(uint8_t &value);
    Packet& operator>>(int16_t &value);
    Packet& operator>>(uint16_t &value);
    Packet& operator>>(int32_t &value);
    Packet& operator>>(uint32_t &value);
    Packet& operator>>(int64_t &value);
    Packet& operator>>(uint64_t &value);
    Packet& operator>>(std::string &str);

    void	getBuffer(char *dest, size_t size);

protected:
	size_t			_rindex;
	size_t			_windex;
	size_t			_size;
	DataBlock		*_data;
	InetAddr		_addr;
};

NET_END_NAMESPACE

#endif /* PACKET_HPP_ */
