/*
 * Error.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: snap
 */

#include <iostream>
#include "NetDef.hpp"
#include "network.h"

#   include <string.h>
#if defined (_WIN32)
#   include <strsafe.h>
#endif

NET_BEGIN_NAMESPACE

std::string		getLastError()
{
#if defined (_WIN32)
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+ 40)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("failed with error %d: %s"), 
        dw, lpMsgBuf);
	std::string tmp = (LPCTSTR)lpDisplayBuf;
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    return tmp;
#elif defined(__linux__)
	char	buffer[1024];
	return ::strerror_r(errno, buffer, 1024);
#else
	return strerror(errno);	
#endif
}

void			printLastError()
{
  #if defined (_WIN32)
  std::string tmp = getLastError();
  MessageBox(NULL, tmp.c_str(), TEXT("Error"), MB_OK);
  std::cerr << tmp << std::endl;
  #else
  std::cerr << getLastError() << std::endl;
  #endif
}

NET_END_NAMESPACE
