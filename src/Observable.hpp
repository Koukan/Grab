#ifndef _OBSERVABLE_
#define _OBSERVABLE_

#include <list>
#include <string>
#include "Observer.hpp"

template <typename Arg>
class Observable
{
public:
	virtual ~Observable()
	{}

	void			registerObserver(Observer<Arg> &observer)
	{
  		typename std::list<Observer<Arg> *>::iterator it =
    	std::find(_observers.begin(), _observers.end(), &observer);
  		if (it == _observers.end())
    		_observers.push_back(&observer);
	}

	void			unregisterObserver(Observer<Arg> &observer)
	{
	   _observers.remove(&observer);
	}

protected:
	Observable()
   	{}

	void			notify(Arg &arg)
	{
  		for (typename std::list<Observer<Arg> *>::iterator it = _observers.begin();
		  it != _observers.end(); ++it)
  		{
    		(*it)->notified(*this, arg);
  		}
	}

private:
	std::list<Observer<Arg> *>    _observers;
};


#endif /* _OBSERVABLE_ */
