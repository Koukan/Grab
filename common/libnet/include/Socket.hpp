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

class EventHandler;

/*!
 \brief Abstraction of a socket
 */
class NET_DLLREQ Socket
{
public:	
	virtual ~Socket();

	/*!
	 \brief Generic Unix way to create a socket

	 \param addr A address to determine the domain: IPV4 or IPv6 or UNIX
	 \param type Type of socket: SOCK_STREAM, SOCK_DGRAM, SOCK_SEQPACKET (only on UNIX) 
	 \param protocol Determine the protocol, may be 0 to select the default protocol

	 \return -1 on failure, >0 otherwise
	 */
	int	open(InetAddr const &addr, int type, int protocol);
	/*!
	 \brief Close the socket

	 \return -1 on failure, >0 otherwise
	 */
	virtual int	close();
	/*!
	 \brief Set the blocking or non blocking mode on the Socket

	 \param flag False to blockin, True to nonblocking

	 \return -1 on failure, >0 otherwise
	 */
	int	setNonBlocking(bool flag);
	/*!
	 \brief Check if blocking 
	 \details Use an internal bool to avoid a syscall, do not modify manually and rely on this function
	 \return True if blocking, False otherwise
	 */
	bool isBlocking() const;
	/*!
	 \brief Allow the address to be reusable
	 \details This option may be a confidentiality issue, use wisely
	 \param flag Allow or not
	 \return -1 on failure, >0 otherwise
	 */
	int	setReuseAddr(bool flag);
	/*!
	 \brief	Modify the default value of the buffer of reception 

	 \param size new size

	 \return -1 on failure, >0 otherwise
	 */
	int setBufferReceiveSize(int size);
	/*!
	 \brief Return the local address on which the Socket is bound 
	 \details This function is a cache to reduce lookup time if repeated
	 \param addr A address to filled

	 \return -1 on failure, >0 otherwise
	 */
	int getLocalAddr(InetAddr &addr) const;
	/*!
	 \brief Return the remote address on which the Socket is bound
	 \details This function is a cache to reduce lookup time if repeated
	 \param addr A address to filled

	 \return -1 on failure, >0 otherwise
	 */
	int getRemoteAddr(InetAddr &addr) const;
	Handle	getHandle() const;
	#if defined (_WIN32)
	Socket(HANDLE handle);
	HANDLE	getAssociatedHandle() const;
	#endif
	void	setHandle(Handle sock);
	EventHandler		*getEventHandler() const;
	void				setEventHandler(EventHandler *handler);

protected:
	Socket();
	int					setSockOpt(int level, int option_name, const sockopt *option_value, socklen_t option_len);

#if defined (_WIN32)
	HANDLE				_associatedHandle;
#endif
	Handle				_handle;
	mutable InetAddr	*_local;
	mutable InetAddr	*_remote;

private:
	bool				_blocking;
	EventHandler		*_nethandler;
	friend class		SocketAcceptor;
};

NET_END_NAMESPACE

#endif /* SOCKET_HPP_ */
