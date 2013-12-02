#pragma once

#include "NetDef.hpp"
#include "EpollPolicy.hpp"
#include "KqueuePolicy.hpp"
#include "WFMOPolicy.hpp"
#include "PollPolicy.hpp"
#include "SelectPolicy.hpp"

NET_BEGIN_NAMESPACE

#if defined (ANDROID)
typedef PollPolicy DefaultSyncPolicy;
#elif defined(__linux__)
typedef EpollPolicy DefaultSyncPolicy;
#elif defined(__FreeBSD__)
typedef KqueuePolicy DefaultSyncPolicy;
#elif defined(__APPLE__)
typedef KqueuePolicy DefaultSyncPolicy;
#elif defined(__MACOSX__)
typedef KqueuePolicy DefaultSyncPolicy;
#elif defined(_WIN32)
typedef SelectPolicy DefaultSyncPolicy;
#else
typedef PollPolicy DefaultSyncPolicy;
#endif

NET_END_NAMESPACE
