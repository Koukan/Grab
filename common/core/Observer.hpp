#ifndef _OBSERVER_
#define _OBSERVER_

CORE_BEGIN_NAMESPACE

template <typename T>
class Observable;

template <typename Arg>
class Observer
{
public:
	virtual ~Observer() {}

protected:
	virtual	void	notified(Observable<Arg> &source, Arg &arg) = 0;
	friend	class 	Observable<Arg>;
};

CORE_END_NAMESPACE

#endif /* _OBSERVER_ */
