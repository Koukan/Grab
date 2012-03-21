#pragma once

#include <list>
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
	virtual ~PacketHandler()
	{
		if (_inpacket)
		  delete _inpacket;
	}

	virtual	int	handleOutput(Socket &sock)
	{
		int ret = 1;

		while (!_outputPacket.empty())
		{
			ret = this->_iohandler.sendPackets(_outputPacket);
			if (ret <= 0)
			{
				if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
					return 1;
				printLastError();
				return ret;
			}
		}
	  	if (_outputPacket.empty())
			this->_reactor->registerHandler(sock, *this, Reactor::READ);
	  	return ret;
	}

	virtual int	handleClose(Socket &socket)
	{
		this->_reactor->removeHandler(socket);
		socket.close();
		delete this;
		return 0;
	}

	void	setSize(size_t size)
	{
		if (_inpacket)
			delete _inpacket;
		_inpacket = new Packet(size);
	}

	virtual int handleInputPacket(Packet &)
	{
		return 0;
	}

	virtual	int handleOutputPacket(Packet const &output)
	{
		_outputPacket.push_back(output);
		this->handleOutput(this->_iohandler);
		if (!_outputPacket.empty())
			this->_reactor->registerHandler(this->_iohandler, *this, Reactor::READ | Reactor::WRITE);
		return 0;
	}


protected:
	PacketHandler(size_t size = 2048) :  _inpacket(0)
	{
		this->setSize(size);
	}

	Packet				*_inpacket;
	std::list<Packet>	_outputPacket;
};

NET_END_NAMESPACE
