#include "Clock.hpp"

NET_USE_NAMESPACE

Clock::Clock() : _paused(false)
{
	this->update();
}

Clock::~Clock()
{
}

void    Clock::play()
{
	_paused = false;
	this->update();
}

void	Clock::pause()
{
 	_paused = true;
}

void    Clock::reset()
{
	_paused = false;
	this->update();
}

bool	Clock::isPaused() const
{
	 return _paused;
}

#if defined (_WIN32)
#define _WINSOCKAPI_
#define EPOCHFILETIME (116444736000000000LL)
#include <windows.h>

void	Clock::update()
{
	 _time = GetTickCount();
}

double	Clock::getElapsedTime() const
{
	if (this->isPaused())
		return 0;
	else
		return (GetTickCount() - _time);
}

uint64_t Clock::getMsSinceEpoch()
{
	FILETIME        ft;
	LARGE_INTEGER   li;

	GetSystemTimeAsFileTime(&ft);
	li.LowPart  = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	uint64_t ret = (li.QuadPart - EPOCHFILETIME) / 10;
	return (ret);
}

std::string Clock::getTimeInStr()
{
   	time_t rawtime = time(0);
	char buffer[26];

    ctime_s(buffer, 26, &rawtime);
	std::string str(buffer);

    if (!str.empty())
    	str.resize(str.size() - 1);
    return (str);
}

void		Clock::sleep(int ms)
{
	::Sleep(ms);
}

#else

#include <sys/time.h>


void	Clock::update()
{
  gettimeofday(&_time, 0);
}

double	Clock::getElapsedTime() const
{
   struct timeval	tmp;

   double		time1;
   double		time2;

	if (this->isPaused())
		return (0);
	gettimeofday(&tmp, 0);
	time1 = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	time2 = _time.tv_sec * 1000 + _time.tv_usec / 1000;
	return (time1 - time2);
}

uint64_t Clock::getMsSinceEpoch()
{
	struct timeval	tmp;

	gettimeofday(&tmp, 0);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}

std::string Clock::getTimeInStr()
{
   	time_t rawtime = time(0);
	char buffer[26];

   	ctime_r(&rawtime, buffer);
	std::string str(buffer);

   	if (!str.empty())
    	str.resize(str.size() - 1);
   	return (str);
}

void		Clock::sleep(int ms)
{
	::usleep(ms * 1000);
}

#endif
