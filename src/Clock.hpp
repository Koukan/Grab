#ifndef _CLOCK_
#define _CLOCK_

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

private:
	bool						_paused;
	OSPolicy					_platform;
};

#if defined (WIN32)

#include "windows.h"

class	WinClock
{
public:
	WinClock(){}
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
	{
	  gettimeofday(&_time, NULL);
	  _begin = _time.tv_sec * 1000 + _time.tv_usec / 1000;
	}
	~UnixClock(){}
	void	update()
	{
	  gettimeofday(&_time, NULL);
	}
	double	getElapsedTime(OSClock<UnixClock> &clock)
	{
	   struct timeval	tmp;

	  double		time1;
	  double		time2;

		if (clock.isPaused())
			return (0);
		gettimeofday(&tmp, NULL);
		time1 = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
		time2 = _time.tv_sec * 1000 + _time.tv_usec / 1000;
		return (time1 - time2);
	}

private:
	struct timeval	_time;
	double		_begin;
};

typedef OSClock<UnixClock> Clock;

#endif

#endif /* _CLOCK_ */
