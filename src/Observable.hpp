#ifndef _OBSERVABLE_
#define _OBSERVABLE_

#include <list>
#include <string>

class Observer;

template <typename Arg>
class Observable
{
public:
	virtual ~Observable()
	{}

	void			registerObserver(Observer<Arg> &observer)
	{	
  		std::list<Observer<Arg> *>::iterator it =
    	find(_observers.begin(), _observers.end(), &observer);
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
  		for (std::list<Observer<Arg> *>::iterator it = _observers.begin();
		  it != _observers.end(); ++it)
  		{
    		(*it)->notified(*this, arg);
  		}
	}

private:
	std::list<Observer<Arg> *>    _observers;
};


#endif /* _OBSERVABLE_ */
