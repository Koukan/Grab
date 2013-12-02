#include <vector>
#include <string.h>
#include "HTTP.hpp"
#include "Base64.hpp"

NET_USE_NAMESPACE

HTTP::Message::Message(double version) : version(version)
{}

HTTP::Response::Response(size_t code, std::string const &message, double version) : HTTP::Message(version), code(code), message(message)
{}

HTTP::Request::Request(std::string const &method, std::string const &location, double version) : HTTP::Message(version), method(method), location(location)
{}

HTTP::POSTRequest::POSTRequest(std::string const &location, std::unordered_map<std::string, std::string> const &values, double version) : HTTP::Request("POST", location, version)
{
	for (auto it = values.begin(); it != values.end(); ++it)
		{
			if (it == values.begin())
				body += it->first + "=" + it->second;
			else
				body += "&" + it->first + "=" + it->second;
		}
}

std::vector<std::string> explode(std::string const &src, std::string const &delim)
{
    std::vector<std::string> ret;
    size_t pos = src.find(delim, 0); 
    for (size_t index = 0; pos != std::string::npos; pos = src.find(delim, index))
    {   
        ret.push_back(src.substr(index, pos - index));
        index = pos + delim.size();
    }   
    return ret;
}

HTTP::ClientService::ClientService() : _response(HTTP::OK, ""), _size_to_read(-1), _chunked(false)
{}

int HTTP::ClientService::handleInput(Socket &)
{
	int             ret = 0;

    do  
    {   
		ret = this->_iohandler.recvPacket(_inpacket, 0, _size_to_read);
    	if (ret == -1 && (errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR))
        	return 1;
        if (ret > 0)
        {   
 	    	_tmp.assign(_inpacket.wr_ptr() - ret, ret);
			int i = 0, read_h = 0;
			if (_size_to_read == -1)
			{
				auto &&lines = explode(_tmp, "\r\n");
				for (auto &line : lines)
				{
					read_h += line.size() + 2;
					if (i == 0 && !parse_code(line, _response))
						return 0;
					else
					{
						size_t pos = line.find(":");
						if (pos != std::string::npos)
							_response.headers[line.substr(0, pos)] = line.substr(pos + 2);
					}
					++i;
					if (line.empty())
						break;
				}
				auto it = _response.headers.find("Transfer-Encoding");
				if (it != _response.headers.end() && it->second == "chunked")
					_chunked = true;
				if (!_chunked)
				{
					int size = std::stoi(_response.headers["Content-Length"]);
					if (size <= 0)
						return 0;
					_size_to_read = size - (ret - read_h) + ret;
				}
			}
			_response.body.append(_inpacket.wr_ptr() - ret + read_h, ret - read_h);
			if (_chunked)
			{
				auto it = _inpacket.getString().find("0\r\n\r\n", _inpacket.getWindex() - ret + read_h);
				if (it == std::string::npos)
					_size_to_read = 4096;
				else
				{
					_size_to_read = 0;
					std::string new_body;
					int i = 0;
					for (auto &line : explode(_response.body, "\r\n"))
					{
						if (i % 2 && !line.empty())
							new_body += line + "\r\n";
						++i;
					}
					_response.body = new_body;
				}
			}
			else
				_size_to_read -= ret;
			if (_size_to_read <= 0)
			{
				if (_handler)
					_handler(_response);
				_response = HTTP::Response(200, "");
				_inpacket.reset();
				_size_to_read = -1;
				_chunked = false;
			}
    	}
    }   
    while (!this->_iohandler.isBlocking());
    return ret;
}

void	HTTP::ClientService::setHandler(std::function<void (Response &response)> handler)
{
	this->_handler = handler;
}

bool	HTTP::ClientService::parse_code(std::string const &line, Response &response)
{
	size_t pos = line.find(" ");
	if (pos == std::string::npos)
		return false;
	size_t index = pos + 1;
	pos = line.find(" ", index);
	if (pos == std::string::npos)
		return false;
	response.version = 1.1;
	response.code = std::stoi(line.substr(index, pos - index));
	response.message = line.substr(index + (pos - index) + 1);
	return true;
}

HTTP::Client::Client(Reactor &reactor, std::string const &domain, int port, bool cookie) : _addr(domain, port), _invalid(false), _cookie(cookie)
{
	_invalid = !this->setup(_addr, reactor);
	_headers["Host"] = domain;
	_headers["Connection"] = "keep-alive";
}

HTTP::Client::~Client()
{

}

void HTTP::Client::setHandler(std::function<void (Response &response)> handler)
{
	this->_service->setHandler(handler);
}

bool HTTP::Client::sendRequest(HTTP::Request const &origin)
{
	HTTP::Request request(origin);
	Packet	packet;
	std::string str;
	str = request.method + " " + request.location + " HTTP/1.1\r\n";
	if (this->_cookie)
		request.headers["Cookie"] = this->cookieString(request.location);
	if (request.body.size() > 0)
		request.headers["Content-Length"] = std::to_string(request.body.size());
	for (auto &header : _headers)
		if (!header.first.empty() && !header.second.empty())
			request.headers[header.first] = header.second;
	for (auto &header : request.headers)
		if (!header.first.empty() && !header.second.empty())
			str += header.first + ": " + header.second + "\r\n";
	str += "\r\n";
	str += request.body;
	packet.addBuffer(str.c_str(), str.size());
	this->_service->handleOutputPacket(packet);
	return true;
}

void HTTP::Client::setCookie(bool flag)
{
	_cookie = flag;
}

void HTTP::Client::setUserAgent(std::string const &agent)
{
	_headers["User-Agent"] = agent;
}

void HTTP::Client::setCredentials(std::string const &user, std::string const &password)
{
	_headers["Authorization"] = "Basic " + Base64::encode(user + ":" + password);
}

void HTTP::Client::addPermanentHeader(std::string const &name, std::string const &value)
{
	_headers[name] = value;
}

std::string HTTP::Client::cookieString(std::string const &location)
{
	std::string ret;
	auto path = _jar.cookies[location];
	for (auto it = path.begin(); it != path.end(); ++it)
	{
		if (it == path.begin())
			ret += it->first + "=" + it->second;
		else
			ret += "," + it->first + "=" + it->second;
	}
	return ret;
}
