#pragma once

#include <deque>
#include <string>
#include <cstring>
#include "NetDef.hpp"
#include "Packet.hpp"
#include "Service.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Utility to send and receive Packet across the network

 \tparam IOType Underlying connection type
 */
template<typename IOType = SocketStream>
class PacketHandler : public Service<IOType>
{
public:
	virtual ~PacketHandler()
	{}

	int	handleOutput(Socket &sock) override
	{
		int ret = 1;

		while (!_outputPacket.empty())
		{
			ret = this->_iohandler.sendPackets(_outputPacket);
			if (ret <= 0)
			{
				if (ret == -1 && wouldBlock())
					return 1;
				printLastError();
				return ret;
			}
			if (_timerid)
				_sent += ret;
		}
		if (_outputPacket.empty() && _write)
		{
			_write = false;
			this->_reactor->registerHandler(sock, *this, Reactor::READ);
		}
	  	return ret;
	}

	int	handleClose(Socket &socket) override
	{
		this->close();
		return 0;
	}

	/*!
	 \brief Fonction to override to handle the packet

	 \param Packet to be treated

	 \return Must return > 0
	 */
	virtual int handleInputPacket(Packet &)
	{
		return 0;
	}

	/*!
	 \brief Send the Packet

	 \param output Packet to send
	 \details A shallow copy is done, so do not modify the packet after calling this function
	 \return Always return 0
	 */
	virtual	int handleOutputPacket(Packet const &output)
	{
		_outputPacket.push_back(output);
		if (_write)
			return 0;
		this->handleOutput(this->_iohandler);
		if (!_outputPacket.empty())
		{
			_write = true;
			this->_reactor->registerHandler(this->_iohandler, *this, Reactor::READ | Reactor::WRITE);
		}
		return 0;
	}

	void	close()
	{
		this->_reactor->removeHandler(this->_iohandler);
		this->_iohandler.close();
		this->handleDeconnection(this->_iohandler);
	}

	void	monitorBandwidth(std::function<void (uint32_t)> func, size_t delay = 1000)
	{
		if (_timerid == 0)
			_timerid = this->_reactor->scheduleTimer([this, func] (size_t) {
			func(_sent);
			_sent = 0;
			}, delay, true);
	}

	void	disableMonitorBandwith()
	{
		if (!_timerid)
			return ;
		this->_reactor->cancelTimer(_timerid);
		_timerid = 0;
	}

protected:
	PacketHandler() : _write(false), _sent(0), _timerid(0)
	{
	}

	virtual void handleDeconnection(Socket &socket)
	{
	}

	Packet			_inpacket;
	std::deque<Packet>	_outputPacket;
	bool			_write;
	uint32_t		_sent;
	uint32_t		_timerid;
};

NET_END_NAMESPACE
