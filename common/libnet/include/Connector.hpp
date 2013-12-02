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
#include "EventHandler.hpp"
#include "Reactor.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Abstraction of a client connecting to a server

 \tparam UserService User-defined class to be instancied when a client sucessfully connect
 \tparam ConnectPolicy Allow to redefine how the client connects
 */
template<typename UserService, typename ConnectPolicy = SocketConnector>
class Connector : public EventHandler
{
public:
	Connector() : _reactor(nullptr), _service(nullptr)
	{}

	~Connector()
	{
		this->close();
		if (_service)
			delete _service;
	}
	/*!
	 \brief Prepare the Connector to connect to a server

	 \param addr Address to connect to, like google.com:80
	 \param reactor A reference to a reactor
	 \param nonBlocking Whether or not the connexion is made on a non-blocking fashion

	 \return false on failure, true otherwise
	 */
	bool		setup(InetAddr const &addr, Reactor &reactor, bool nonBlocking = false)
	{
		_reactor = &reactor;
		if (_connector.setup(addr) == -1)
			return false;
		_service = new UserService();
		_service->setReactor(reactor);
		if (nonBlocking)
			_connector.setNonBlocking(nonBlocking);
		int con = _connector.connect(_service->getIOHandler(), addr);
		if (con == -1 && (errno == EWOULDBLOCK || errno == EINPROGRESS))
			return _reactor->registerHandler(_connector, *this, Reactor::WRITE);
		else if (con != -1)
		{
		    _connector.setHandle(INVALID_HANDLE);
			_reactor->registerHandler(_service->getIOHandler(), *_service, _service->getReactorFlags());
			_service->init();
			return true;
		}
		return false;
	}

	int		handleOutput(Socket &socket) override
	{
		InetAddr	tmp;
		if (_connector.getRemoteAddr(tmp) != -1)
		{
			_service->getIOHandler().setHandle(_connector.getHandle());
			_connector.setHandle(INVALID_HANDLE);
			_reactor->registerHandler(_service->getIOHandler(), *_service, _service->getReactorFlags());
			_service->init();
		}
	  return 1;
	}

	void	close()
	{
		if (_reactor && _service)
	  		_reactor->removeHandler(_service->getIOHandler());
		if (_service)
			_service->close();
	}

protected:
	Reactor 		*_reactor;
	UserService		*_service;
	ConnectPolicy 	_connector;
};

NET_END_NAMESPACE

#endif /* CONNECTOR_HPP_ */
