/*
 * Socket.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: snap
 */

#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include "NetDef.hpp"
#include "network.h"
#include "InetAddr.hpp"

NET_BEGIN_NAMESPACE

class NetHandler;

class NET_DLLREQ Socket
{
public:
	int	open(InetAddr const &addr, int type, int protocol);
	int	close();

	int	setNonBlocking(bool flag);
	bool isBlocking() const;
	int	setReuseAddr(bool flag);
	int getLocalAddr(InetAddr &addr) const;
	int getRemoteAddr(InetAddr &addr) const;
	Handle	getHandle() const;
	void	setHandle(Handle sock);
	NetHandler			*getNetHandler() const;
	void				setNetHandler(NetHandler *handler);
	Socket();
	virtual ~Socket();

protected:

	Handle				_handle;
	mutable InetAddr	*_local;
	mutable InetAddr	*_remote;

private:
	int		setSockOpt(int level, int option_name, const sockopt *option_value, socklen_t option_len);
	bool				_blocking;
	NetHandler			*_nethandler;
	friend class		SocketAcceptor;
};

NET_END_NAMESPACE

#endif /* SOCKET_HPP_ */
