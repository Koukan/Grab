#pragma once

#if defined(__linux__)
#include "EpollPolicy.hpp"
#define DefaultSyncPolicy EpollPolicy
#elif defined(_WI2)
#include "WFMOPolicy.hpp"
#define DefaultSyncPolicy WFMOPolicy
#else
#include "PollPolicy.hpp"
#define DefaultSyncPolicy PollPolicy
#endif
