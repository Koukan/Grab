/*
 * Service.hpp
 *
 *  Created on: Nov 9, 2011
 *      Author: snap
 */

#ifndef SERVICE_HPP_
#define SERVICE_HPP_

#include "Reactor.hpp"
#include "NetHandler.hpp"
#include "SocketStream.hpp"

template<typename IOType = SocketStream>
class Service : public NetHandler, public IOType
{
public:
	Service(int flags = Reactor::READ) : _reactor(0), _flags(flags)
	{}

	virtual ~Service()
	{
	  if (_reactor)
	   _reactor->cancelTimer(*this);
	}

	virtual	void	init() {};

	void	setReactor(Reactor &reactor)
	{
		_reactor = &reactor;
	}

	int		getReactorFlags()
	{
		return _flags;
	}

protected:
	Reactor	*_reactor;

private:
	int		_flags;
};

#endif /* SERVICE_HPP_ */
