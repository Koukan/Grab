
#ifndef _CLOCK_
#define _CLOCK_

#include <stdint.h>
#include <string>
#include <time.h>
#include "NetDef.hpp"

#if defined (_WIN32)
#define _WINSOCKAPI_
#define EPOCHFILETIME (116444736000000000LL)
#include <windows.h>
#else
#include <sys/time.h>
#endif

NET_BEGIN_NAMESPACE

# if defined (_WIN32)
typedef	DWORD clocktime_t;
#else
typedef struct timeval clocktime_t;
# endif

class NET_DLLREQ Clock
{
public:
	Clock();
	~Clock();

	void	play();
	void	pause();
	void	update();
	void	reset();
	bool	isPaused() const;

	double	getElapsedTime() const;
	static uint64_t getMsSinceEpoch();
	static std::string getTimeInStr();
	static void			sleep(int ms);

private:
	bool						_paused;
	clocktime_t					_time;
};

NET_END_NAMESPACE

#endif /* _CLOCK_ */
