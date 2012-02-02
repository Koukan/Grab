#pragma once

#include "NetDef.hpp"
#include "EpollPolicy.hpp"
#include "KqueuePolicy.hpp"
#include "WFMOPolicy.hpp"
#include "PollPolicy.hpp"

NET_BEGIN_NAMESPACE

#if defined(__linux__)
typedef EpollPolicy DefaultSyncPolicy;
#elif defined(__FreeBSD__)
typedef KqueuePolicy DefaultSyncPolicy;
#elif defined(_WI2)
typedef WFMOPolicy DefaultSyncPolicy;
#else
typedef PollPolicy DefaultSyncPolicy;
#endif

NET_END_NAMESPACE
