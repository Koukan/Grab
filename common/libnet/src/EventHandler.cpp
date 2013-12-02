/*
 * EventHandler.cpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#include "EventHandler.hpp"

NET_USE_NAMESPACE

EventHandler::EventHandler()
{}

EventHandler::~EventHandler()
{
}

int	EventHandler::handleInput(Socket &)
{
	return 0;
}

int	EventHandler::handleOutput(Socket &)
{
	return 0;
}

int	EventHandler::handleClose(Socket &)
{
	return 0;
}

void	EventHandler::handleTimeout(size_t)
{
}
