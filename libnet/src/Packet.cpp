/*
 * Packet.cpp
 *
 *  Created on: Nov 20, 2011
 *      Author: snap
 */

#include <iostream>
#include <cstring>
#include "Packet.hpp"

NET_USE_NAMESPACE

Packet::Packet(size_t size) : _rindex(0), _windex(0), _size(0)
{
	_data = new DataBlock(size);
}

Packet::Packet(DataBlock &data, size_t size) : _rindex(0), _windex(0), _size(size)
{
  _data = &data;
  data.seize();
}

Packet::Packet(Packet const &other)
{
   if (&other != this)
   {
	  this->_rindex = 0;
	  this->_windex = 0;
	  this->_size = other._size;
	  this->_data = other._data;
	  this->_addr = other._addr;
	  if (this->_data)
		  this->_data->seize();
   }
}

Packet::~Packet()
{
	this->release();
}

Packet	*Packet::clone()
{
	if (!_data)
	  return 0;
	Packet	*ret = new Packet(this->size());
	::memcpy(ret->base(), this->base(), this->size());
	return ret;
}

Packet	*Packet::duplicate() const
{
 if (!_data)
	  return 0;
  Packet *ret = new Packet(*_data, _size);
  ret->setDestination(_addr);
  return ret;
}

void	Packet::release()
{
  if (_data)
  {
	  _data->release();
	  _data = 0;
  }
}

size_t	Packet::size() const
{
	return this->_size;
}

size_t	Packet::capacity() const
{
	return ((_data) ? _data->_vec.iov_len : 0);
}

char	*Packet::rd_ptr()
{
  return &(this->base())[_rindex];
}

char	*Packet::wr_ptr()
{
  return &(this->base())[_windex];
}

void	Packet::rd_ptr(size_t index)
{
  _rindex = (index < this->capacity()) ? index : this->capacity();
}

void	Packet::wr_ptr(size_t index)
{
  _windex = (index < this->capacity()) ? index : this->capacity();
}

char	*Packet::base() const
{
  return static_cast<char*>(_data->_vec.iov_base);
}

DataBlock	*Packet::getDataBlock() const
{
  return _data;
}

void	Packet::reset()
{
  _windex = 0;
  _rindex = 0;
  _size = 0;
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
  return _windex >= _size;
}

bool	Packet::isFull() const
{
	return _windex >= this->capacity();
}

InetAddr	&Packet::getAddr()
{
  return _addr;
}

Packet& Packet::operator<<(bool value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  tmp[_windex++] = static_cast<char>(value);
  if (_size < _windex)
	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(char value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  tmp[_windex++] = static_cast<char>(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(int8_t value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  tmp[_windex++] = static_cast<char>(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(uint8_t value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  tmp[_windex++] = static_cast<char>(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(int16_t value)
{
  int16_t *tmp = reinterpret_cast<int16_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
  *tmp = htons(value);
  _windex += sizeof(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(uint16_t value)
{
  uint16_t *tmp = reinterpret_cast<uint16_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
  *tmp = htons(value);
  _windex += sizeof(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(int32_t value)
{
	int32_t *tmp = reinterpret_cast<int32_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
	*tmp = htonl(value);
	_windex += sizeof(value);
	 if (_size < _windex)
		_size = _windex;
	return *this;
}

Packet& Packet::operator<<(uint32_t value)
{
	uint32_t *tmp = reinterpret_cast<uint32_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
	*tmp = htonl(value);
	_windex += sizeof(value);
	 if (_size < _windex)
		_size = _windex;
	return *this;
}

Packet& Packet::operator<<(int64_t value)
{
	uint64_t *tmp = reinterpret_cast<uint64_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
	*tmp = htonll(value);
	_windex += sizeof(value);
	 if (_size < _windex)
		_size = _windex;
	return *this;
}

Packet& Packet::operator<<(uint64_t value)
{
  uint64_t *tmp = reinterpret_cast<uint64_t*>(&static_cast<char*>(_data->_vec.iov_base)[_windex]);
  *tmp = htonll(value);
  _windex += sizeof(value);
  if (_size < _windex)
 	_size = _windex;
  return *this;
}

Packet& Packet::operator<<(std::string const &str)
{
  char *tmp = &static_cast<char*>(_data->_vec.iov_base)[_windex];
  if (str.size() < this->capacity() - _windex)
  {
	  ::memcpy(tmp, str.c_str(), str.size() + 1);
	  _windex += str.size() + 1;
	  if (_size < _windex)
	 	_size = _windex;
  }
  return *this;
}

Packet& Packet::operator<<(char const *str)
{
  return *this << std::string(str);
}

Packet& Packet::operator>>(bool &value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  value = tmp[_rindex++] > 0;
  return *this;
}

Packet& Packet::operator>>(char &value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  value = tmp[_rindex++];
  return *this;
}

Packet& Packet::operator>>(int8_t &value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  value = tmp[_rindex++];
  return *this;
}

Packet& Packet::operator>>(uint8_t &value)
{
  char *tmp = static_cast<char*>(_data->_vec.iov_base);
  value = tmp[_rindex++];
  return *this;
}

Packet& Packet::operator>>(int16_t &value)
{
  int16_t *tmp = reinterpret_cast<int16_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohs(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(uint16_t &value)
{
  uint16_t *tmp = reinterpret_cast<uint16_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohs(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(int32_t &value)
{
  int32_t *tmp = reinterpret_cast<int32_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohl(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(uint32_t &value)
{
  int32_t *tmp = reinterpret_cast<int32_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohl(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(int64_t &value)
{
  int64_t *tmp = reinterpret_cast<int64_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohll(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(uint64_t &value)
{
  uint64_t *tmp = reinterpret_cast<uint64_t*>(&static_cast<char*>(_data->_vec.iov_base)[_rindex]);
  value = ntohll(*tmp);
  _rindex += sizeof(value);
  return *this;
}

Packet& Packet::operator>>(std::string &str)
{
  char *tmp = &static_cast<char*>(_data->_vec.iov_base)[_rindex];
  str.assign(tmp, ::strnlen(tmp, this->size()));
  _rindex += str.size() + 1;
  return *this;
}

void	Packet::setSize(size_t size)
{
	_size = size;
}

void	Packet::setDestination(InetAddr const &addr)
{
	_addr = addr;
}

void	Packet::addBuffer(char *src, size_t size)
{
  char *tmp = &static_cast<char*>(_data->_vec.iov_base)[_windex];
  ::memcpy(tmp, src, size);
  _windex += size;
  _size += size;
}

void	Packet::getBuffer(char *dest, size_t size)
{
  char *tmp = &static_cast<char*>(_data->_vec.iov_base)[_rindex];
  size_t res = _size - _rindex;
  ::memcpy(dest, tmp, ((size < res) ? size : res));
  _rindex += size;
}
