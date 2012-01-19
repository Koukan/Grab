#include "network.h"
#include "SetupNetwork.hpp"

NET_USE_NAMESPACE

#if defined (_WIN32)
SetupNetwork::SetupNetwork()
{
  WSADATA       wsaData;
  
  WSAStartup(MAKEWORD(2, 2), &wsaData); 
}

SetupNetwork::~SetupNetwork()
{
  WSACleanup();
}

#else

SetupNetwork::SetupNetwork()
{

}

SetupNetwork::~SetupNetwork()
{
}

#endif
