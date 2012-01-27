#ifndef _OBSERVER_
#define _OBSERVER_

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


#endif /* _OBSERVER_ */
