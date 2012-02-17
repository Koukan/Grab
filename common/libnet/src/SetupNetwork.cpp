#include "network.h"
#include "SetupNetwork.hpp"
#include "PoolAllocator.hpp"

NET_USE_NAMESPACE

#if defined (_WIN32)
SetupNetwork::SetupNetwork()
{
  WSADATA       wsaData;
  
  WSAStartup(MAKEWORD(2, 2), &wsaData);
  PoolAllocator::init(); 
}

SetupNetwork::~SetupNetwork()
{
  WSACleanup();
}

#else

SetupNetwork::SetupNetwork()
{
	PoolAllocator::init();
}

SetupNetwork::~SetupNetwork()
{
}

#endif
