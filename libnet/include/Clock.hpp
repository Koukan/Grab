
#ifndef _CLOCK_
#define _CLOCK_

#include <stdint.h>
#include <string>
#include <time.h>
#include "NetDef.hpp"

NET_BEGIN_NAMESPACE

template <typename OSPolicy>
class OSClock
{
public:
	OSClock() : _paused(false)
	{
		this->update();
	}

	virtual ~OSClock(){}

	void	play()
	{
		_paused = false;
		this->update();
	}

	void	pause()
	{
	  _paused = true;
	}

	void	update()
	{
	  _platform.update();
	}

	void	reset()
	{
	  _paused = false;
	  this->update();
	}

	double	getElapsedTime()
	{
	  return _platform.getElapsedTime(*this);
	}

	bool	isPaused()
	{
	  return _paused;
	}

	static uint64_t getMsSinceEpoch()
	{
		return OSPolicy::getMsSinceEpoch();
	}

	static std::string getTimeInStr()
	{
		return OSPolicy::getTimeInStr();
	}

	static void			sleep(int ms)
	{
		return OSPolicy::sleep(ms);
	}

private:
	bool						_paused;
	OSPolicy					_platform;
};

#if defined (_WIN32)
#define _WINSOCKAPI_
#define EPOCHFILETIME (116444736000000000LL)

#include <windows.h>

class	WinClock
{
public:
	WinClock()
	{}

	~WinClock(){}

	void	update()
	{
	  _time = GetTickCount();
	}

	double	getElapsedTime(OSClock<WinClock> &clock)
	{
		if (clock.isPaused())
			return 0;
		else
			return (GetTickCount() - _time);
	}

	static uint64_t getMsSinceEpoch()
	{
		FILETIME        ft;
		LARGE_INTEGER   li;

		GetSystemTimeAsFileTime(&ft);
		li.LowPart  = ft.dwLowDateTime;
		li.HighPart = ft.dwHighDateTime;
		uint64_t ret = (li.QuadPart - EPOCHFILETIME) / 10;
		return (ret);
	}

	static std::string getTimeInStr()
  	{
    	time_t rawtime = time(0);
		char buffer[26];

    	ctime_s(buffer, 26, &rawtime);
		std::string str(buffer);

    	if (!str.empty())
      		str.resize(str.size() - 1);
    	return (str);
  	}

	static void		sleep(int ms)
	{
		::Sleep(ms);
	}

private:
	DWORD	_time;
};

typedef OSClock<WinClock> Clock;

#else

#include <sys/time.h>

class	UnixClock
{
public:
	UnixClock()
	{}

	~UnixClock(){}

	void	update()
	{
	  gettimeofday(&_time, 0);
	}

	double	getElapsedTime(OSClock<UnixClock> &clock)
	{
	   struct timeval	tmp;

	  double		time1;
	  double		time2;

		if (clock.isPaused())
			return (0);
		gettimeofday(&tmp, 0);
		time1 = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
		time2 = _time.tv_sec * 1000 + _time.tv_usec / 1000;
		return (time1 - time2);
	}

	static uint64_t getMsSinceEpoch()
	{
		struct timeval	tmp;

		gettimeofday(&tmp, 0);
		return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
	}

	static std::string getTimeInStr()
  	{
    	time_t rawtime = time(0);
		char buffer[26];

    	ctime_r(&rawtime, buffer);
		std::string str(buffer);

    	if (!str.empty())
      	str.resize(str.size() - 1);
    	return (str);
  	}

	static void		sleep(int ms)
	{
		::usleep(ms * 1000);
	}

private:
	struct timeval	_time;
};

typedef OSClock<UnixClock> Clock;

#endif

NET_END_NAMESPACE

#endif /* _CLOCK_ */
