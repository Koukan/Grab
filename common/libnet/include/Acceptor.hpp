/*
 * Acceptor.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef ACCEPTOR_HPP_
#define ACCEPTOR_HPP_

#include "network.h"
#include "Reactor.hpp"
#include "EventHandler.hpp"
#include "InetAddr.hpp"
#include "SocketAcceptor.hpp"
#include "Service.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Abstraction of a server accepting client

 \tparam UserService User-defined class to be instancied whenever a client is connecting
 \tparam AcceptPolicy Allow to redefine how the client is accepted
 */
template<typename UserService, typename AcceptPolicy = SocketAcceptor>
class	Acceptor : public EventHandler
{
public:
	Acceptor() : _reactor(nullptr), _nonblocking(false)
	{
	}

	~Acceptor()
	{
		this->close();
	}

	/*!
	 \brief prepare the Acceptor to receive client

	 \param addr Address to listen, like 0.0.0.0:80
	 \param reactor A reference to a Reactor
	 \param nonblocking Whether or not a client is accepted on a non-blocking fashion
	 \return false on failure true otherwise
	 */
	bool		setup(InetAddr const &addr, Reactor &reactor, bool nonblocking = true)
	{
		_reactor = &reactor;
		_nonblocking = nonblocking;
		if (_acceptor.setup(addr) == -1)
			return false;
		return _reactor->registerHandler(_acceptor, *this, Reactor::ACCEPT);
	}

	int	handleInput(Socket &) override
	{
	  UserService	*stream = new UserService();
	  int	ret = _acceptor.accept(stream->getIOHandler(), 0, _nonblocking);
	  if (ret != -1)
	  {
		stream->setReactor(*_reactor);
		_reactor->registerHandler(stream->getIOHandler(), *stream, stream->getReactorFlags());
		stream->init();
	  }
	  else
		 delete stream;
	  return ret;
	}

	AcceptPolicy	&getAcceptorPolicy()
	{
		return _acceptor;
	}

	/*!
	 \brief Close the sokets and finalize the object
	 */
	void	close()
	{
		_acceptor.close();	
		if (_reactor)
	  		_reactor->removeHandler(_acceptor);
	}

private:
	AcceptPolicy _acceptor;
	Reactor *_reactor;
	bool	_nonblocking;
};

NET_END_NAMESPACE

#endif /* ACCEPTOR_HPP_ */
