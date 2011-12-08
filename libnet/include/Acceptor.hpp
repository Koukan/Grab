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

NET_BEGIN_NAMESPACE

template<typename Service, typename AcceptPolicy = SocketAcceptor>
class	Acceptor : public NetHandler
{
public:
	Acceptor() : _reactor(0)
	{
	}

	~Acceptor()
	{
	  _reactor->removeHandler(acceptor);
	}

	int		setup(InetAddr const &addr, Reactor &reactor)
	{
		_reactor = &reactor;
		int ret = acceptor.setup(addr);
		if (ret != -1)
		  _reactor->registerHandler(acceptor, *this, Reactor::ACCEPT);
		return ret;
	}

	virtual	int	handleInput(Socket &)
	{
	  Service	*stream = new Service();
	  int	ret = acceptor.accept(*stream, 0);
	  if (ret != -1)
	  {
		stream->setReactor(*_reactor);
		_reactor->registerHandler(*stream, *stream, stream->getReactorFlags());
		stream->init();
	  }
	  else
		 delete stream;
	  return ret;
	}

private:
	AcceptPolicy acceptor;
	Reactor *_reactor;
};

NET_END_NAMESPACE

#endif /* ACCEPTOR_HPP_ */
