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
#include "NetHandler.hpp"
#include "InetAddr.hpp"
#include "SocketAcceptor.hpp"
#include "Service.hpp"

NET_BEGIN_NAMESPACE

template<typename UserService, typename AcceptPolicy = SocketAcceptor>
class	Acceptor : public NetHandler
{
public:
	Acceptor() : _reactor(0), _nonblocking(false)
	{
	}

	~Acceptor()
	{
		if (_reactor)
	  		_reactor->removeHandler(acceptor);
	}

	int		setup(InetAddr const &addr, Reactor &reactor, bool nonblocking = true)
	{
		_reactor = &reactor;
		_nonblocking = nonblocking;
		int ret = _acceptor.setup(addr);
		if (ret != -1)
		  _reactor->registerHandler(_acceptor, *this, Reactor::ACCEPT);
		return ret;
	}

	virtual	int	handleInput(Socket &)
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

private:
	AcceptPolicy _acceptor;
	Reactor *_reactor;
	bool	_nonblocking;
};

NET_END_NAMESPACE

#endif /* ACCEPTOR_HPP_ */
