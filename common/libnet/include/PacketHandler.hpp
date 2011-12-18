#pragma once

#include <list>
#include <set>
#include <string>
#include <cstring>
#include "NetDef.hpp"
#include "Packet.hpp"
#include "Service.hpp"

NET_BEGIN_NAMESPACE

template<typename IOType = SocketStream>
class PacketHandler : public Service<IOType>
{
public:
	PacketHandler(size_t size = 2048, std::string const &deli = "") :  _delimiter(deli), _inpacket(0), _enableWhitelist(false)
	{
		this->setSize(size);
	}

	virtual ~PacketHandler()
	{
		if (_inpacket)
		  delete _inpacket;
	}

	virtual	int	handleInput(Socket &)
	{
		do
		{
		  int	ret = this->recv(*_inpacket);
		  if (ret > 0)
		  {
			  if (_inpacket->isFull())
			  {
				  _inpacket->wr_ptr(0);
				  if (_delimiter.empty())
				  {
					Packet	packet(*_inpacket);
					this->handleInputPacket(packet);
				  }
			  }
			  else if (!_delimiter.empty())
			  {
				  size_t	windex = _inpacket->getWindex();
				  char	*base = _inpacket->base();
				  char	*current = base;
				  size_t prev = std::string::npos;
				  _tmp.assign(base, windex);
				  size_t pos = _tmp.find(_delimiter, 0);
				  for (; pos != std::string::npos; pos = _tmp.find(_delimiter, pos + _delimiter.size()))
				  {
					  base[pos] = '\0';
					  _temp.assign(current, &base[pos] - current);
					  Packet	result(_temp, _temp._vec.iov_len);
					  if (this->handleInputPacket(result) <= 0)
						  return -1;
					  current =  &base[pos + _delimiter.size()];
					  prev = pos;
				  }
				  if (prev != std::string::npos)
				  {
					  prev = windex - prev - _delimiter.size();
					  ::memmove(base, current, prev);
					  _inpacket->wr_ptr(prev);
				  }
			  }
		  }
		  if (ret == -1 && (errno == EWOULDBLOCK || errno == EINTR))
			return 1;
		  return ret;
		}
		while (!this->isBlocking());
	   return 0;
	}

	virtual	int	handleOutput(Socket &)
	{
		int ret = 0;
		Packet	*top;

		while (!_outputPacket.empty())
		{
			  top = _outputPacket.front();
			  ret = this->send(*top);
			  if (ret <= 0)
			  {
				  if (ret == -1 && (errno == EWOULDBLOCK || errno == EINTR))
					  return 1;
				  printLastError();
				  return ret;
			  }
			  if (top->isConsumned())
			  {
				  top->release();
				  delete top;
				  _outputPacket.pop_front();
			  }
			  if (this->isBlocking())
				return ret;
		 }
	  if (_outputPacket.empty())
		this->_reactor->registerHandler(*this, *this, Reactor::READ);
	  return ret;
	}

	virtual int	handleClose(Socket &socket)
	{
		this->_reactor->removeHandler(socket);
		this->close();
		for (std::list<Packet*>::iterator it = _outputPacket.begin(); it != _outputPacket.end(); ++it)
			delete *it;
		delete this;
		return 0;
	}

	void	setSize(size_t size)
	{
		if (_inpacket)
			delete _inpacket;
		_inpacket = new Packet(size);
	}

	void	setDelimiter(std::string const &deli)
	{
		this->_delimiter = deli;
	}

	virtual int handleInputPacket(Packet &)
	{
		return 0;
	}

	virtual	int handleOutputPacket(Packet &output)
	{
		if (_outputPacket.empty())
			this->_reactor->registerHandler(*this, *this, Reactor::READ | Reactor::WRITE);
		_outputPacket.push_back(output.duplicate());
		return 0;
	}

	void	enableWhitelist(bool enable)
	{
		_enableWhitelist = enable;
	}

	void	addAddr(InetAddr const &addr)
	{
		_whitelist.insert(addr);
	}

	void	removeAddr(InetAddr const &addr)
	{
		_whitelist.erase(addr);
	}

	void	clearAddr()
	{
		_whitelist.clear();
	}

protected:
	std::string			_tmp;
	std::string			_delimiter;
	Packet				*_inpacket;
	bool				_enableWhitelist;
	std::set<InetAddr>	_whitelist;
	DataBlock			_temp;
	std::list<Packet*>	_outputPacket;
};

NET_END_NAMESPACE
