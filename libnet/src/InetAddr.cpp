#include "Converter.hpp"
#include "InetAddr.hpp"
#include <stdlib.h>
#include <string.h>

NET_USE_NAMESPACE

InetAddr::InetAddr(Family family)
{
	addr_.ss_family = family;
	this->setPort(0);
	this->setAnyAddr();
}

InetAddr::InetAddr(sockaddr &addr, socklen_t size)
{
	this->assign(addr, size);
}

InetAddr::InetAddr(std::string const &host, unsigned short port, Family family, int flags)
{
	this->initAddr(host, Converter::toString<unsigned short>(port), family, flags);
}

InetAddr::InetAddr(std::string const &host, std::string const &port, Family family, int flags)
{
	this->initAddr(host, port, family, flags);
}

InetAddr::InetAddr(unsigned short port, Family family, int flags)
{
	this->initAddr("", Converter::toString<unsigned short>(port), family, flags | AI_PASSIVE);
}

InetAddr::InetAddr(std::string const &port, Family family, int flags)
{
	this->initAddr("", port, family, flags | AI_PASSIVE);
}

void	InetAddr::assign(sockaddr &addr, socklen_t size)
{
  ::memcpy(&addr_, &addr, size);
  len_ = size;
}

int		InetAddr::initAddr(std::string const &host, std::string const &port, int family, int flags)
{
	 struct addrinfo *cpy;
	 struct addrinfo hints;
	 struct addrinfo *result;

	 ::memset(&hints, 0, sizeof(hints));
	 hints.ai_family = family;
	 hints.ai_flags = flags;
	 int res = ::getaddrinfo((host.empty() ? 0 : host.c_str()), port.c_str(), &hints, &result);
	 if (res || !result)
	    return res;
	 for (cpy = result; cpy; cpy = 0)
	 {
	  ::memcpy(&addr_, cpy->ai_addr, cpy->ai_addrlen);
	  len_ = cpy->ai_addrlen;
	 }
	 ::freeaddrinfo(result);
	 return res;
}

void	InetAddr::setAnyAddr()
{
  if (addr_.ss_family == AF_INET)
	  (reinterpret_cast<struct sockaddr_in *>(&addr_))->sin_addr.s_addr = INADDR_ANY;
  else if (addr_.ss_family == AF_INET6)
	  (reinterpret_cast<struct sockaddr_in6 *>(&addr_))->sin6_addr = in6addr_any;
}

void	InetAddr::setPort(std::string const &port)
{
  struct servent *serv = ::getservbyname(port.c_str(), 0);
  if (serv)
    this->setPort(serv->s_port);
}

void	InetAddr::setPort(unsigned short port)
{
  if (addr_.ss_family == AF_INET)
   reinterpret_cast<struct sockaddr_in *>(&this->addr_)->sin_port = htons(port);
  else if (addr_.ss_family == AF_INET6)
   reinterpret_cast<struct sockaddr_in6 *>(&this->addr_)->sin6_port = htons(port);
}

void    InetAddr::setHost(std::string const &host)
{
	initAddr(host, Converter::toString<unsigned short>(this->getPort()), this->getFamily(), 0);
}

int  	InetAddr::getPort() const
{
 if (addr_.ss_family == AF_INET)
   return ntohs((reinterpret_cast<struct sockaddr_in const *>(&addr_))->sin_port);
 else if (addr_.ss_family == AF_INET6)
   return ntohs((reinterpret_cast<struct sockaddr_in6 const *>(&addr_))->sin6_port);
 else
   return -1;
}

std::string const	&InetAddr::getHost(int flags, bool refresh) const
{
 if (!host_.empty() && !refresh)
   return host_;
 char hbuf[NI_MAXHOST];

 int ret = ::getnameinfo(reinterpret_cast<sockaddr const*>(&addr_), len_, hbuf, sizeof(hbuf), 0, 0, flags);
 if (ret == -1)
 {
	 printLastError();
	 host_.clear();
 }
 else
	host_ = hbuf;
 return host_;
}

InetAddr::Family		InetAddr::getFamily() const
{
  return static_cast<Family>(addr_.ss_family);
}

socklen_t			InetAddr::getSize() const
{
  return len_;
}

bool				InetAddr::isAnyAddr() const
{
	if (addr_.ss_family == AF_INET)
		return ((reinterpret_cast<struct sockaddr_in const *>(&addr_))->sin_addr.s_addr == INADDR_ANY);
	else if (addr_.ss_family == AF_INET6)
		return (::memcmp(&((reinterpret_cast<struct sockaddr_in6 const *>(&addr_))->sin6_addr), &in6addr_any, sizeof(in6addr_any)) == 0);
	else
		return false;
}

bool				InetAddr::isMulticast() const
{
	if (addr_.ss_family == AF_INET)
		return IN_MULTICAST(ntohl((reinterpret_cast<struct sockaddr_in const *>(&addr_))->sin_addr.s_addr));
	else if (addr_.ss_family == AF_INET6)
		return IN6_IS_ADDR_MULTICAST(&((reinterpret_cast<struct sockaddr_in6 const *>(&addr_))->sin6_addr)) != 0;
	else
		return false;
}

bool				InetAddr::isLoopback() const
{
	if (addr_.ss_family == AF_INET)
		return ((reinterpret_cast<struct sockaddr_in const *>(&addr_))->sin_addr.s_addr == INADDR_LOOPBACK);
	else if (addr_.ss_family == AF_INET6)
		return IN6_IS_ADDR_LOOPBACK(&((reinterpret_cast<struct sockaddr_in6 const *>(&addr_))->sin6_addr)) != 0;
	else
		return false;
}

InetAddr::operator sockaddr const *() const
{
  return reinterpret_cast<sockaddr const *>(&addr_);
}

bool	InetAddr::operator<(InetAddr const &other) const
{
	return len_ < other.getSize();
}

bool 	InetAddr::operator==(InetAddr const & other) const
{
	return (::memcmp(&addr_, &other.addr_, len_) == 0);
}

bool 	InetAddr::operator!=(InetAddr const & other) const
{
	return !(*this == other);
}
