/*
 * Connector.hpp
 *
 *  Created on: Nov 11, 2011
 *      Author: snap
 */

#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

#include <iostream>
#include "network.h"
#include "SocketConnector.hpp"
#include "NetHandler.hpp"
#include "Reactor.hpp"

NET_BEGIN_NAMESPACE

template<typename Service, typename ConnectPolicy = SocketConnector>
class Connector : public NetHandler
{
public:
	Connector() : _reactor(0), _service(0)
	{}

	~Connector()
	{
	  if (_reactor)
		_reactor->removeHandler(_connector);
	}

	int		setup(InetAddr const &addr, Reactor &reactor, bool nonBlocking = true)
	{
		_reactor = &reactor;
		int ret = _connector.setup(addr);
		if (ret != -1)
		{
		   _service = new Service();
		   _service->setReactor(reactor);
		   if (nonBlocking)
			 _connector.setNonBlocking(nonBlocking);
		   int con = _connector.connect(*_service, addr);
		   if (con == -1 && ( errno == EWOULDBLOCK  || errno == EINPROGRESS))
			_reactor->registerHandler(_connector, *this, Reactor::WRITE);
		   else if (con != -1)
		   {
			_reactor->registerHandler(*_service, *_service, _service->getReactorFlags());
			_service->init();
		   }
		   if (!nonBlocking)
			 return con;
		}
		return ret;
	}

	virtual	int	handleOutput(Socket &)
	{
	  InetAddr	tmp;
	  if (_connector.getRemoteAddr(tmp) != -1)
	  {
		_service->setHandle(_connector.getHandle());
		_reactor->registerHandler(*_service, *_service, _service->getReactorFlags());
		_service->init();
	  }
	  return 1;
	}

private:
	Reactor *_reactor;
	Service	*_service;
	ConnectPolicy _connector;
};

NET_END_NAMESPACE

#endif /* CONNECTOR_HPP_ */
