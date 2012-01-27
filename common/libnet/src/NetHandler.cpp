/*
 * NetHandler.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#include "NetHandler.hpp"

NET_USE_NAMESPACE

NetHandler::NetHandler()
{}

NetHandler::~NetHandler()
{
}

int	NetHandler::handleInput(Socket &)
{
	return 0;
}

int	NetHandler::handleOutput(Socket &)
{
	return 0;
}

int	NetHandler::handleClose(Socket &)
{
	return 0;
}

int	NetHandler::handleTimeout()
{
	return 0;
}
