#include "network.h"
#include "SetupNetwork.hpp"
#include "PoolAllocator.hpp"

#if defined (_WIN32)
#include <Socketapi.h>
//#pragma comment(lib, "Windows.Networking.lib")
#endif

NET_USE_NAMESPACE

#if defined (_WIN32)
SetupNetwork::SetupNetwork()
{
	WSADATA       wsaData;
  
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//SetSocketMediaStreamingMode(TRUE);
}

SetupNetwork::~SetupNetwork()
{
	//SetSocketMediaStreamingMode(FALSE);
	WSACleanup();
}

#else

SetupNetwork::SetupNetwork()
{}

SetupNetwork::~SetupNetwork()
{}

#endif
