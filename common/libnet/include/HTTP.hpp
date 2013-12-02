#pragma once
#include "PacketHandler.hpp"
#include "Connector.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

NET_BEGIN_NAMESPACE

namespace HTTP {

enum Code
{
	Continue = 100,
	Swicthing_Protocol = 101,
	Connection_timed_out = 118,
	OK = 200,
	Created = 201,
	Accepted = 202,
	Non_Authoritative_Information = 203,
	No_Content = 204,
	Reset_Content = 205,
	Partial_Content = 206,
	Multiples_Choices = 300,
	Moved_Permanently = 301,
	Moved_Temporarily = 302,
	See_Other = 303,
	Not_Modified = 304,
	Bad_Request = 400,
	Unauthorized = 401,
	Forbidden = 403,
	Not_Found = 404,
	Internal_Server_Error = 500,
	Not_Implemented = 501,
	Bad_Gateway = 502,
	Service_Unavailable = 503
};



class NET_DLLREQ Message
{
public:
	Message(double version = 1.1);
	double	version;
	std::unordered_map<std::string, std::string>	headers;
	std::string body;
};

class NET_DLLREQ Response : public Message
{
public:
	Response(size_t code, std::string const &message, double version = 1.1);
	size_t code;
	std::string message;	
};

class NET_DLLREQ Request : public Message
{
public:
	Request(std::string const &method, std::string const &location, double version = 1.1);
	std::string method;
	std::string location;
};

class NET_DLLREQ POSTRequest : public Request
{
public:
	POSTRequest(std::string const &location, std::unordered_map<std::string, std::string> const &values, double version = 1.1);
};

class NET_DLLREQ ClientService : public PacketHandler<SocketStream>
{
public:
	ClientService();
	int	handleInput(Socket &) override;
	void setHandler(std::function<void (Response &response)> handler);

private:
	bool	parse_code(std::string const &line, Response &response);

	Response		_response;
	int				_size_to_read;
	bool			_chunked;
	std::string 	_tmp;
	std::function<void (Response &response)>	_handler;
};

class NET_DLLREQ CookieJar
{
public:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string> >	cookies;
};

class NET_DLLREQ Client : public Connector<ClientService>
{
public:
	Client(Reactor &reactor, std::string const &domain, int port = 80, bool cookie = true);
	~Client();
	void setHandler(std::function<void (Response &response)> handler);
	bool sendRequest(Request const &request);
	void setCookie(bool flag);
	void setUserAgent(std::string const &agent);
	void setCredentials(std::string const &user, std::string const &password);
	void addPermanentHeader(std::string const &name, std::string const &value);

private:
	std::string	cookieString(std::string const &location);

	InetAddr	_addr;
	bool		_invalid;
	bool		_cookie;
	CookieJar	_jar;
	std::unordered_map<std::string, std::string> _headers;
};

};

NET_END_NAMESPACE

