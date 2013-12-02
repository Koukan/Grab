/*
 * Packet.cpp
 *
 *  Created on: Dec 3, 2011
 *      Author: snap
 */

#include "Packet.hpp"

NET_USE_NAMESPACE

Packet::Packet() : _rindex(0), _windex(0), _size(0), _ss(new std::string)
{
}

Packet::~Packet()
{
}

Packet::Packet(Packet const &other)
{
	if (this != &other)
	{
		this->_rindex = 0;
		this->_windex = 0;
		this->_size = other._size;
		this->_ss = other._ss;
		this->_addr = other._addr;
	}
}

Packet::Packet(Packet &&other) : _rindex(0), _windex(0), _size(other._size),
								 _addr(std::move(other._addr)), _ss(std::move(other._ss))
{}

Packet&	Packet::operator=(Packet const &other)
{
	if (this != &other)
	{	
		this->_rindex = 0;
		this->_windex = 0;
		this->_size = other._size;
		this->_ss = other._ss;
		this->_addr = other._addr;
	}
	return *this;
}

Packet& Packet::operator<<(std::string const &str)
{
	uint16_t tmp = str.size();
	*this << tmp;
	this->addBuffer(str.c_str(), tmp);
	return *this;
}

Packet& Packet::operator>>(std::string &str)
{
	uint16_t size;
	*this >> size;
	if (size > _size - _rindex)
		throw std::runtime_error("Insuffient place to extract data");
	str.assign(rd_ptr(), size);
	_rindex += size;
	return *this;
}

Packet& Packet::operator<<(std::wstring const &str)
{
	*this << (uint16_t)str.size();
	this->addBuffer(reinterpret_cast<const char *>(str.c_str()), str.size() * sizeof(wchar_t));
	return *this;
}

Packet& Packet::operator>>(std::wstring &str)
{
	uint16_t slen;
	*this >> slen;
	if (slen > _size - _rindex)
		throw std::runtime_error("Insuffient place to extract data");
	str.assign(reinterpret_cast<const wchar_t *>(rd_ptr()), slen);
	_rindex += slen;
	return *this;
}

void	Packet::addBuffer(char const *buf, size_t size)
{
	if (!_ss.unique())
		_ss.reset(new std::string(this->base(), this->size()));
	if (_windex == _size)
		_ss->append(buf, size);
	else
		_ss->insert(_windex, buf, size);
	_windex += size;
	_size = _ss->size();
}

char const	*Packet::rd_ptr()
{
	return _ss->c_str() + _rindex;
}

char const	*Packet::wr_ptr()
{
	return _ss->c_str() + _windex;
}

void	Packet::rd_ptr(size_t index)
{
	_rindex = index;
}

void	Packet::wr_ptr(size_t index)
{
	_windex = index;
}

size_t	Packet::size() const
{
	return _size;
}

void	Packet::setSize(size_t size)
{
	_size = size;
}

char const	*Packet::base() const
{
	return _ss->c_str();
}

void	Packet::reset()
{
	_windex = 0;
	_rindex = 0;
	_size = 0;
	_ss->clear();
}

size_t	Packet::getRindex() const
{
	return _rindex;
}

size_t	Packet::getWindex() const
{
	return _windex;
}

bool	Packet::isConsumned() const
{
	return (_windex == _size);
}

InetAddr const	&Packet::getAddr() const
{
	return _addr;
}

void	Packet::setDestination(InetAddr const &addr)
{
	_addr = addr;
}

std::string const &Packet::getString() const
{
	return *_ss;
}

void	Packet::reserve(size_t size)
{
	_ss->reserve(size);
}

void	Packet::assign(std::string &&string)
{
	_ss->append(string);
	_size = _ss->size();
}
