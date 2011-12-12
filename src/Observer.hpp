#ifndef _OBSERVER_
#define _OBSERVER_

#include "Observable.hpp"

template <typename Arg>
class Observer
{
public:
	virtual ~Observer() {}

protected:
	virtual	void	notified(Observable &source, Arg &arg) = 0;
	friend	class 	Observable<Arg>;
};


#endif /* _OBSERVER_ */
