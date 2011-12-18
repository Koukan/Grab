/*
 * Error.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: snap
 */

#include <iostream>
#include "NetDef.hpp"
#include "network.h"

#if defined (__unix__)
#	include <string.h>
#endif

NET_BEGIN_NAMESPACE

std::string		getLastError()
{
	char	buffer[1024];
#if defined (_WIN32)
    if (::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                           NULL, errno, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)(buffer), 0, NULL) == 0)
            return "Unknown error";
    else
            return buffer;
    //::LocalFree(buf);
#elif defined(__linux__)
	return ::strerror_r(errno, buffer, 1024);
#else
	return strerror(errno);	
#endif
}

void			printLastError()
{
  std::cerr << getLastError() << std::endl;
}

NET_END_NAMESPACE
