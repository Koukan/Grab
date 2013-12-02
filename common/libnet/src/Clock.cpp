#include <thread>
#include <ctime>
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

void	Clock::update()
{
	_clock = Clock::clock::now();
}

uint64_t	Clock::getElapsedTime() const
{
	if (this->isPaused())
		return 0;
	else
		return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clock).count());
}

uint64_t	Clock::getMsSinceEpoch()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void		Clock::sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string Clock::getTimeInStr(std::string const &format)
{
	char			tmp[256];
	std::time_t		t = std::time(nullptr);
	std::tm			tm;
#if defined (_WIN32)
	localtime_s(&tm, &t);
	std::strftime(tmp, sizeof(tmp), format.c_str(), &tm);
#else
	std::strftime(tmp, sizeof(tmp), format.c_str(), localtime_r(&t, &tm));
#endif
	return tmp;
}

/* will be usefull for Android
#include <sys/time.h>

void	Clock::update()
{
  gettimeofday(&_time, 0);
}

uint64_t	Clock::getElapsedTime() const
{
   struct timeval	tmp;

   uint64_t		time1;
   uint64_t		time2;

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
   	return ctime(&rawtime);
}

void		Clock::sleep(int ms)
{
	::usleep(ms * 1000);
}
*/
