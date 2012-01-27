#pragma once

#include "NetDef.hpp"
#include "EpollPolicy.hpp"
#include "KqueuePolicy.hpp"
#include "WFMOPolicy.hpp"
#include "PollPolicy.hpp"

#if defined(__linux__)
#define DefaultSyncPolicy NET_NAMESPACE::EpollPolicy
#elif defined(__FreeBSD__)
#define DefaultSyncPolicy NET_NAMESPACE::KqueuePolicy
#elif defined(_WI2)
#define DefaultSyncPolicy NET_NAMESPACE::WFMOPolicy
#else
#define DefaultSyncPolicy NET_NAMESPACE::PollPolicy
#endif
