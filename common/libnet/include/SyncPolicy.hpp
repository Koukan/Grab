#pragma once

#include "NetDef.hpp"

#if defined(__linux__)
#include "EpollPolicy.hpp"
#define DefaultSyncPolicy NET_NAMESPACE::EpollPolicy
#elif defined(__FreeBSD__)
#include "KqueuePolicy.hpp"
#define DefaultSyncPolicy NET_NAMESPACE::KqueuePolicy
#elif defined(_WI2)
#include "WFMOPolicy.hpp"
#define DefaultSyncPolicy NET_NAMESPACE::WFMOPolicy
#else
#include "PollPolicy.hpp"
#define DefaultSyncPolicy NET_NAMESPACE::PollPolicy
#endif
