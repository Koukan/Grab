#pragma once
#include <string>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

namespace Base64
{
	std::string encode(std::string const &s);
	std::string encode(unsigned char const* , unsigned int len);
	std::string decode(std::string const& s);
};

NET_END_NAMESPACE
