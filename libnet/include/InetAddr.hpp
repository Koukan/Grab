#ifndef _INETADDR_
#define _INETADDR_

#include "NetDef.hpp"
#include "network.h"
#include <string>

NET_BEGIN_NAMESPACE

class NET_DLLREQ InetAddr
{
public:
	enum Family
	{
		IPV4 = AF_INET,
		IPV6 = AF_INET6,
		UNSPEC = AF_UNSPEC
	};
	InetAddr(Family family = IPV4);
	InetAddr(sockaddr &addr, socklen_t size);
	InetAddr(std::string const &host, unsigned short port, Family family = IPV4, int flags = 0);
	InetAddr(std::string const &host, std::string const &port, Family family = IPV4, int flags = 0);
	InetAddr(unsigned short port, Family family = IPV4, int flags = 0);
	InetAddr(std::string const &port, Family family = IPV4, int flags = 0);
	void		assign(sockaddr &addr, socklen_t size);
	void		setAnyAddr();
	void		setPort(std::string const &port);
	void		setPort(unsigned short port);
	void		setHost(std::string const &host);
	int 		getPort() const;
	std::string const &	getHost(int flags = 0, bool refresh = false) const;
	Family		getFamily() const;
	socklen_t	getSize() const;

	bool		isAnyAddr() const;
	bool		isMulticast() const;
	bool		isLoopback() const;

	operator	sockaddr const *() const;
	bool operator<(InetAddr const & other) const;
	bool operator==(InetAddr const & other) const;
	bool operator!=(InetAddr const & other) const;


private:
	int			initAddr(std::string const &host, std::string const &port, int family = AF_UNSPEC, int flags = 0);

	mutable std::string	host_;
	struct sockaddr_storage	addr_;
	socklen_t		len_;
};

NET_END_NAMESPACE

#endif /* _INETADDR_ */
