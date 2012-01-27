#ifndef _CONDITIONVAR_
#define _CONDITIONVAR_

#include "NetDef.hpp"


#if defined  (_WIN32)
#define _WINSOCKAPI_
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "Mutex.hpp"

NET_BEGIN_NAMESPACE

# if defined (_WIN32)
typedef	CONDITION_VARIABLE cond_t;
#else
typedef pthread_cond_t cond_t;
# endif

class NET_DLLREQ ConditionVar : public Mutex
{
public:
	ConditionVar();
	~ConditionVar();
	bool	signal();
	bool	broadcast();
	bool	uniqueWait();
	bool	uniqueTimedWait(int ms);
	bool	wait();
	bool	timedWait(int ms);

private:
	cond_t 	_cond;
};

NET_END_NAMESPACE

#endif /* _CONDITIONVAR_ */
