#pragma once

#include <unordered_map>
#include <tuple>
#include "NetDef.hpp"
#include "network.h"
#include "Reactor.hpp"
#include "EventHandler.hpp"

NET_BEGIN_NAMESPACE

/*!
 \brief Reactor based on select()
 \details Available on all platforms
 */
class NET_DLLREQ SelectPolicy : public Reactor
{
public:
	SelectPolicy();
	~SelectPolicy();

	bool	registerHandler(Socket &socket, EventHandler &handler, int mask) override;
	bool	removeHandler(Socket &socket) override;
	int		waitForEvent(int timeout = -1) override;


private:
	size_t	_maxfd;
	size_t	_rsize;
	size_t	_wsize;
	size_t	_esize;
	fd_set	_read_set;
	fd_set	_write_set;
	fd_set	_except_set;
	std::unordered_map<Socket *, int>	_sockets;
};

NET_END_NAMESPACE