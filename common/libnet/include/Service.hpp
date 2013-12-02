/*
 * Service.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include "NetDef.hpp"
#include "Reactor.hpp"
#include "EventHandler.hpp"
#include "SocketStream.hpp"

NET_BEGIN_NAMESPACE

template<typename IOHandler = SocketStream>
class Service : public EventHandler
{
public:
	Service(int flags = Reactor::READ) : _reactor(0), _flags(flags)
	{}

	virtual ~Service()
	{
//	  if (_reactor)
//	   _reactor->cancelTimer(*this);
	}

	virtual	void	init() {};

	void	setReactor(Reactor &reactor)
	{
		_reactor = &reactor;
	}

	int		getReactorFlags() const
	{
		return _flags;
	}

	IOHandler	&getIOHandler()
	{
		return _iohandler;
	}

protected:
	Reactor		*_reactor;
	IOHandler	_iohandler;

private:
	int		_flags;
};

NET_END_NAMESPACE

#endif /* SERVICE_HPP_ */
