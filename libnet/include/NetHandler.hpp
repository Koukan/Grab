/*
 * NetHandler.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef NETHANDLER_HPP_
#define NETHANDLER_HPP_

#include "network.h"
#include <Socket.hpp>

class NetHandler
{
public:
	NetHandler();
	virtual ~NetHandler();

	virtual	int	handleInput(Socket &handle);
	virtual	int	handleOutput(Socket &handle);
	virtual int	handleClose(Socket &handle);
	virtual	int	handleTimeout();

private:
};

#endif /* NETHANDLER_HPP_ */
