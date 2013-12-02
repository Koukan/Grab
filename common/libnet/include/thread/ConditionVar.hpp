#ifndef _CONDITIONVAR_
#define _CONDITIONVAR_

#include "NetDef.hpp"


#include <functional>
#if defined  (_WIN32) && _MSC_VER < 1700
#define _WINSOCKAPI_
#include <windows.h>
#else
#include <condition_variable>
#endif

#include "Mutex.hpp"

NET_BEGIN_NAMESPACE

# if (defined (_WIN32) && _MSC_VER < 1700) || defined (ANDROID)
class NET_DLLREQ ConditionVar
{
public:
	ConditionVar();
	~ConditionVar();
	void	notify_one();
	void	notify_all();
	void	wait(Mutex &mutex);
	void	wait(Mutex &mutex, std::function<bool ()> predicate);
	bool	wait_for(Mutex &mutex, int ms);

private:
#if defined (_WIN32)
	CONDITION_VARIABLE 	_cond;
#else
	pthread_cond_t		_cond;
#endif
};
#else
typedef std::condition_variable ConditionVar;
# endif

NET_END_NAMESPACE

#endif /* _CONDITIONVAR_ */
