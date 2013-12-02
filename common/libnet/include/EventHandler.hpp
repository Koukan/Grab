/*
 * EventHandler.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef NETHANDLER_HPP_
#define NETHANDLER_HPP_

#include "NetDef.hpp"
#include "network.h"
#include <Socket.hpp>

NET_BEGIN_NAMESPACE

/*!
 \brief Class with event hook
 */
class NET_DLLREQ EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler();
	/*!
	 \brief Called when a read/input event occured

	 \param handle Handle which triggers the event
	 \details if the fonction return <0 then the connection is considered closed
	 \return must return >0
	 */
	virtual	int	handleInput(Socket &handle);
	/*!
	 \brief Called when a write/output event occured 

	 \param handle Handle which triggers the event
	 \details if the fonction return <0 then the connection is considered closed
	 \return must return >0
	 */
	virtual	int	handleOutput(Socket &handle);
	/*!
	 \brief Called when a close event occured 

	 \param handle Handle which triggers the event

	 \return must return >0
	 */
	virtual int	handleClose(Socket &handle);
	/*!
	 \brief Called when a timeout event occured 

	 \param realDelay time elasped really

	 \return must return >0
	 */
	virtual	void	handleTimeout(size_t realDelay);

private:
};

NET_END_NAMESPACE

#endif /* NETHANDLER_HPP_ */
